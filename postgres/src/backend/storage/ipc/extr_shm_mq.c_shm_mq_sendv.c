#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ shm_mq_result ;
struct TYPE_8__ {scalar_t__ len; char* data; } ;
typedef  TYPE_1__ shm_mq_iovec ;
struct TYPE_9__ {int mqh_length_word_complete; int mqh_partial_bytes; int mqh_counterparty_attached; TYPE_3__* mqh_queue; } ;
typedef  TYPE_2__ shm_mq_handle ;
struct TYPE_10__ {scalar_t__ mq_sender; int /*<<< orphan*/  mq_mutex; TYPE_4__* mq_receiver; scalar_t__ mq_detached; } ;
typedef  TYPE_3__ shm_mq ;
struct TYPE_11__ {int /*<<< orphan*/  procLatch; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_4__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MAXALIGN_DOWN (scalar_t__) ; 
 int MAXIMUM_ALIGNOF ; 
 scalar_t__ MyProc ; 
 scalar_t__ SHM_MQ_DETACHED ; 
 scalar_t__ SHM_MQ_SUCCESS ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ shm_mq_send_bytes (TYPE_2__*,scalar_t__,char*,int,scalar_t__*) ; 

shm_mq_result
shm_mq_sendv(shm_mq_handle *mqh, shm_mq_iovec *iov, int iovcnt, bool nowait)
{
	shm_mq_result res;
	shm_mq	   *mq = mqh->mqh_queue;
	PGPROC	   *receiver;
	Size		nbytes = 0;
	Size		bytes_written;
	int			i;
	int			which_iov = 0;
	Size		offset;

	Assert(mq->mq_sender == MyProc);

	/* Compute total size of write. */
	for (i = 0; i < iovcnt; ++i)
		nbytes += iov[i].len;

	/* Try to write, or finish writing, the length word into the buffer. */
	while (!mqh->mqh_length_word_complete)
	{
		Assert(mqh->mqh_partial_bytes < sizeof(Size));
		res = shm_mq_send_bytes(mqh, sizeof(Size) - mqh->mqh_partial_bytes,
								((char *) &nbytes) + mqh->mqh_partial_bytes,
								nowait, &bytes_written);

		if (res == SHM_MQ_DETACHED)
		{
			/* Reset state in case caller tries to send another message. */
			mqh->mqh_partial_bytes = 0;
			mqh->mqh_length_word_complete = false;
			return res;
		}
		mqh->mqh_partial_bytes += bytes_written;

		if (mqh->mqh_partial_bytes >= sizeof(Size))
		{
			Assert(mqh->mqh_partial_bytes == sizeof(Size));

			mqh->mqh_partial_bytes = 0;
			mqh->mqh_length_word_complete = true;
		}

		if (res != SHM_MQ_SUCCESS)
			return res;

		/* Length word can't be split unless bigger than required alignment. */
		Assert(mqh->mqh_length_word_complete || sizeof(Size) > MAXIMUM_ALIGNOF);
	}

	/* Write the actual data bytes into the buffer. */
	Assert(mqh->mqh_partial_bytes <= nbytes);
	offset = mqh->mqh_partial_bytes;
	do
	{
		Size		chunksize;

		/* Figure out which bytes need to be sent next. */
		if (offset >= iov[which_iov].len)
		{
			offset -= iov[which_iov].len;
			++which_iov;
			if (which_iov >= iovcnt)
				break;
			continue;
		}

		/*
		 * We want to avoid copying the data if at all possible, but every
		 * chunk of bytes we write into the queue has to be MAXALIGN'd, except
		 * the last.  Thus, if a chunk other than the last one ends on a
		 * non-MAXALIGN'd boundary, we have to combine the tail end of its
		 * data with data from one or more following chunks until we either
		 * reach the last chunk or accumulate a number of bytes which is
		 * MAXALIGN'd.
		 */
		if (which_iov + 1 < iovcnt &&
			offset + MAXIMUM_ALIGNOF > iov[which_iov].len)
		{
			char		tmpbuf[MAXIMUM_ALIGNOF];
			int			j = 0;

			for (;;)
			{
				if (offset < iov[which_iov].len)
				{
					tmpbuf[j] = iov[which_iov].data[offset];
					j++;
					offset++;
					if (j == MAXIMUM_ALIGNOF)
						break;
				}
				else
				{
					offset -= iov[which_iov].len;
					which_iov++;
					if (which_iov >= iovcnt)
						break;
				}
			}

			res = shm_mq_send_bytes(mqh, j, tmpbuf, nowait, &bytes_written);

			if (res == SHM_MQ_DETACHED)
			{
				/* Reset state in case caller tries to send another message. */
				mqh->mqh_partial_bytes = 0;
				mqh->mqh_length_word_complete = false;
				return res;
			}

			mqh->mqh_partial_bytes += bytes_written;
			if (res != SHM_MQ_SUCCESS)
				return res;
			continue;
		}

		/*
		 * If this is the last chunk, we can write all the data, even if it
		 * isn't a multiple of MAXIMUM_ALIGNOF.  Otherwise, we need to
		 * MAXALIGN_DOWN the write size.
		 */
		chunksize = iov[which_iov].len - offset;
		if (which_iov + 1 < iovcnt)
			chunksize = MAXALIGN_DOWN(chunksize);
		res = shm_mq_send_bytes(mqh, chunksize, &iov[which_iov].data[offset],
								nowait, &bytes_written);

		if (res == SHM_MQ_DETACHED)
		{
			/* Reset state in case caller tries to send another message. */
			mqh->mqh_length_word_complete = false;
			mqh->mqh_partial_bytes = 0;
			return res;
		}

		mqh->mqh_partial_bytes += bytes_written;
		offset += bytes_written;
		if (res != SHM_MQ_SUCCESS)
			return res;
	} while (mqh->mqh_partial_bytes < nbytes);

	/* Reset for next message. */
	mqh->mqh_partial_bytes = 0;
	mqh->mqh_length_word_complete = false;

	/* If queue has been detached, let caller know. */
	if (mq->mq_detached)
		return SHM_MQ_DETACHED;

	/*
	 * If the counterparty is known to have attached, we can read mq_receiver
	 * without acquiring the spinlock and assume it isn't NULL.  Otherwise,
	 * more caution is needed.
	 */
	if (mqh->mqh_counterparty_attached)
		receiver = mq->mq_receiver;
	else
	{
		SpinLockAcquire(&mq->mq_mutex);
		receiver = mq->mq_receiver;
		SpinLockRelease(&mq->mq_mutex);
		if (receiver == NULL)
			return SHM_MQ_SUCCESS;
		mqh->mqh_counterparty_attached = true;
	}

	/* Notify receiver of the newly-written data, and return. */
	SetLatch(&receiver->procLatch);
	return SHM_MQ_SUCCESS;
}