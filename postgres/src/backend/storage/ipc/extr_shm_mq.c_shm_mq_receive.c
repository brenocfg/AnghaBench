#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ shm_mq_result ;
struct TYPE_9__ {int mqh_counterparty_attached; int mqh_consume_pending; int mqh_length_word_complete; int mqh_partial_bytes; int mqh_expected_bytes; int mqh_buflen; int /*<<< orphan*/ * mqh_buffer; int /*<<< orphan*/  mqh_context; int /*<<< orphan*/  mqh_handle; TYPE_2__* mqh_queue; } ;
typedef  TYPE_1__ shm_mq_handle ;
struct TYPE_10__ {scalar_t__ mq_receiver; int mq_detached; int mq_ring_size; int /*<<< orphan*/  mq_sender; } ;
typedef  TYPE_2__ shm_mq ;
typedef  int Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int MAXALIGN (int) ; 
 int MAXIMUM_ALIGNOF ; 
 int MQH_INITIAL_BUFSIZE ; 
 int Max (int,int) ; 
 void* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MyProc ; 
 scalar_t__ SHM_MQ_DETACHED ; 
 scalar_t__ SHM_MQ_SUCCESS ; 
 scalar_t__ SHM_MQ_WOULD_BLOCK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int shm_mq_counterparty_gone (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shm_mq_get_sender (TYPE_2__*) ; 
 int /*<<< orphan*/  shm_mq_inc_bytes_read (TYPE_2__*,int) ; 
 scalar_t__ shm_mq_receive_bytes (TYPE_1__*,int,int,int*,void**) ; 
 int /*<<< orphan*/  shm_mq_wait_internal (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

shm_mq_result
shm_mq_receive(shm_mq_handle *mqh, Size *nbytesp, void **datap, bool nowait)
{
	shm_mq	   *mq = mqh->mqh_queue;
	shm_mq_result res;
	Size		rb = 0;
	Size		nbytes;
	void	   *rawdata;

	Assert(mq->mq_receiver == MyProc);

	/* We can't receive data until the sender has attached. */
	if (!mqh->mqh_counterparty_attached)
	{
		if (nowait)
		{
			int			counterparty_gone;

			/*
			 * We shouldn't return at this point at all unless the sender
			 * hasn't attached yet.  However, the correct return value depends
			 * on whether the sender is still attached.  If we first test
			 * whether the sender has ever attached and then test whether the
			 * sender has detached, there's a race condition: a sender that
			 * attaches and detaches very quickly might fool us into thinking
			 * the sender never attached at all.  So, test whether our
			 * counterparty is definitively gone first, and only afterwards
			 * check whether the sender ever attached in the first place.
			 */
			counterparty_gone = shm_mq_counterparty_gone(mq, mqh->mqh_handle);
			if (shm_mq_get_sender(mq) == NULL)
			{
				if (counterparty_gone)
					return SHM_MQ_DETACHED;
				else
					return SHM_MQ_WOULD_BLOCK;
			}
		}
		else if (!shm_mq_wait_internal(mq, &mq->mq_sender, mqh->mqh_handle)
				 && shm_mq_get_sender(mq) == NULL)
		{
			mq->mq_detached = true;
			return SHM_MQ_DETACHED;
		}
		mqh->mqh_counterparty_attached = true;
	}

	/*
	 * If we've consumed an amount of data greater than 1/4th of the ring
	 * size, mark it consumed in shared memory.  We try to avoid doing this
	 * unnecessarily when only a small amount of data has been consumed,
	 * because SetLatch() is fairly expensive and we don't want to do it too
	 * often.
	 */
	if (mqh->mqh_consume_pending > mq->mq_ring_size / 4)
	{
		shm_mq_inc_bytes_read(mq, mqh->mqh_consume_pending);
		mqh->mqh_consume_pending = 0;
	}

	/* Try to read, or finish reading, the length word from the buffer. */
	while (!mqh->mqh_length_word_complete)
	{
		/* Try to receive the message length word. */
		Assert(mqh->mqh_partial_bytes < sizeof(Size));
		res = shm_mq_receive_bytes(mqh, sizeof(Size) - mqh->mqh_partial_bytes,
								   nowait, &rb, &rawdata);
		if (res != SHM_MQ_SUCCESS)
			return res;

		/*
		 * Hopefully, we'll receive the entire message length word at once.
		 * But if sizeof(Size) > MAXIMUM_ALIGNOF, then it might be split over
		 * multiple reads.
		 */
		if (mqh->mqh_partial_bytes == 0 && rb >= sizeof(Size))
		{
			Size		needed;

			nbytes = *(Size *) rawdata;

			/* If we've already got the whole message, we're done. */
			needed = MAXALIGN(sizeof(Size)) + MAXALIGN(nbytes);
			if (rb >= needed)
			{
				mqh->mqh_consume_pending += needed;
				*nbytesp = nbytes;
				*datap = ((char *) rawdata) + MAXALIGN(sizeof(Size));
				return SHM_MQ_SUCCESS;
			}

			/*
			 * We don't have the whole message, but we at least have the whole
			 * length word.
			 */
			mqh->mqh_expected_bytes = nbytes;
			mqh->mqh_length_word_complete = true;
			mqh->mqh_consume_pending += MAXALIGN(sizeof(Size));
			rb -= MAXALIGN(sizeof(Size));
		}
		else
		{
			Size		lengthbytes;

			/* Can't be split unless bigger than required alignment. */
			Assert(sizeof(Size) > MAXIMUM_ALIGNOF);

			/* Message word is split; need buffer to reassemble. */
			if (mqh->mqh_buffer == NULL)
			{
				mqh->mqh_buffer = MemoryContextAlloc(mqh->mqh_context,
													 MQH_INITIAL_BUFSIZE);
				mqh->mqh_buflen = MQH_INITIAL_BUFSIZE;
			}
			Assert(mqh->mqh_buflen >= sizeof(Size));

			/* Copy partial length word; remember to consume it. */
			if (mqh->mqh_partial_bytes + rb > sizeof(Size))
				lengthbytes = sizeof(Size) - mqh->mqh_partial_bytes;
			else
				lengthbytes = rb;
			memcpy(&mqh->mqh_buffer[mqh->mqh_partial_bytes], rawdata,
				   lengthbytes);
			mqh->mqh_partial_bytes += lengthbytes;
			mqh->mqh_consume_pending += MAXALIGN(lengthbytes);
			rb -= lengthbytes;

			/* If we now have the whole word, we're ready to read payload. */
			if (mqh->mqh_partial_bytes >= sizeof(Size))
			{
				Assert(mqh->mqh_partial_bytes == sizeof(Size));
				mqh->mqh_expected_bytes = *(Size *) mqh->mqh_buffer;
				mqh->mqh_length_word_complete = true;
				mqh->mqh_partial_bytes = 0;
			}
		}
	}
	nbytes = mqh->mqh_expected_bytes;

	if (mqh->mqh_partial_bytes == 0)
	{
		/*
		 * Try to obtain the whole message in a single chunk.  If this works,
		 * we need not copy the data and can return a pointer directly into
		 * shared memory.
		 */
		res = shm_mq_receive_bytes(mqh, nbytes, nowait, &rb, &rawdata);
		if (res != SHM_MQ_SUCCESS)
			return res;
		if (rb >= nbytes)
		{
			mqh->mqh_length_word_complete = false;
			mqh->mqh_consume_pending += MAXALIGN(nbytes);
			*nbytesp = nbytes;
			*datap = rawdata;
			return SHM_MQ_SUCCESS;
		}

		/*
		 * The message has wrapped the buffer.  We'll need to copy it in order
		 * to return it to the client in one chunk.  First, make sure we have
		 * a large enough buffer available.
		 */
		if (mqh->mqh_buflen < nbytes)
		{
			Size		newbuflen = Max(mqh->mqh_buflen, MQH_INITIAL_BUFSIZE);

			while (newbuflen < nbytes)
				newbuflen *= 2;

			if (mqh->mqh_buffer != NULL)
			{
				pfree(mqh->mqh_buffer);
				mqh->mqh_buffer = NULL;
				mqh->mqh_buflen = 0;
			}
			mqh->mqh_buffer = MemoryContextAlloc(mqh->mqh_context, newbuflen);
			mqh->mqh_buflen = newbuflen;
		}
	}

	/* Loop until we've copied the entire message. */
	for (;;)
	{
		Size		still_needed;

		/* Copy as much as we can. */
		Assert(mqh->mqh_partial_bytes + rb <= nbytes);
		memcpy(&mqh->mqh_buffer[mqh->mqh_partial_bytes], rawdata, rb);
		mqh->mqh_partial_bytes += rb;

		/*
		 * Update count of bytes that can be consumed, accounting for
		 * alignment padding.  Note that this will never actually insert any
		 * padding except at the end of a message, because the buffer size is
		 * a multiple of MAXIMUM_ALIGNOF, and each read and write is as well.
		 */
		Assert(mqh->mqh_partial_bytes == nbytes || rb == MAXALIGN(rb));
		mqh->mqh_consume_pending += MAXALIGN(rb);

		/* If we got all the data, exit the loop. */
		if (mqh->mqh_partial_bytes >= nbytes)
			break;

		/* Wait for some more data. */
		still_needed = nbytes - mqh->mqh_partial_bytes;
		res = shm_mq_receive_bytes(mqh, still_needed, nowait, &rb, &rawdata);
		if (res != SHM_MQ_SUCCESS)
			return res;
		if (rb > still_needed)
			rb = still_needed;
	}

	/* Return the complete message, and reset for next message. */
	*nbytesp = nbytes;
	*datap = mqh->mqh_buffer;
	mqh->mqh_length_word_complete = false;
	mqh->mqh_partial_bytes = 0;
	return SHM_MQ_SUCCESS;
}