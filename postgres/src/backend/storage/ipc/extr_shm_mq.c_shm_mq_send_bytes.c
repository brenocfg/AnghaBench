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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  shm_mq_result ;
struct TYPE_9__ {int mqh_counterparty_attached; int /*<<< orphan*/  mqh_handle; TYPE_2__* mqh_queue; } ;
typedef  TYPE_1__ shm_mq_handle ;
struct TYPE_10__ {scalar_t__ mq_ring_size; int mq_detached; scalar_t__ mq_ring_offset; int /*<<< orphan*/ * mq_ring; TYPE_4__* mq_receiver; int /*<<< orphan*/  mq_bytes_written; int /*<<< orphan*/  mq_bytes_read; } ;
typedef  TYPE_2__ shm_mq ;
struct TYPE_11__ {int /*<<< orphan*/  procLatch; } ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ MAXALIGN (scalar_t__) ; 
 scalar_t__ Min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHM_MQ_DETACHED ; 
 int /*<<< orphan*/  SHM_MQ_SUCCESS ; 
 int /*<<< orphan*/  SHM_MQ_WOULD_BLOCK ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAIT_EVENT_MQ_SEND ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ pg_atomic_read_u64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_compiler_barrier () ; 
 int /*<<< orphan*/  pg_memory_barrier () ; 
 scalar_t__ shm_mq_counterparty_gone (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shm_mq_get_receiver (TYPE_2__*) ; 
 int /*<<< orphan*/  shm_mq_inc_bytes_written (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  shm_mq_wait_internal (TYPE_2__*,TYPE_4__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static shm_mq_result
shm_mq_send_bytes(shm_mq_handle *mqh, Size nbytes, const void *data,
				  bool nowait, Size *bytes_written)
{
	shm_mq	   *mq = mqh->mqh_queue;
	Size		sent = 0;
	uint64		used;
	Size		ringsize = mq->mq_ring_size;
	Size		available;

	while (sent < nbytes)
	{
		uint64		rb;
		uint64		wb;

		/* Compute number of ring buffer bytes used and available. */
		rb = pg_atomic_read_u64(&mq->mq_bytes_read);
		wb = pg_atomic_read_u64(&mq->mq_bytes_written);
		Assert(wb >= rb);
		used = wb - rb;
		Assert(used <= ringsize);
		available = Min(ringsize - used, nbytes - sent);

		/*
		 * Bail out if the queue has been detached.  Note that we would be in
		 * trouble if the compiler decided to cache the value of
		 * mq->mq_detached in a register or on the stack across loop
		 * iterations.  It probably shouldn't do that anyway since we'll
		 * always return, call an external function that performs a system
		 * call, or reach a memory barrier at some point later in the loop,
		 * but just to be sure, insert a compiler barrier here.
		 */
		pg_compiler_barrier();
		if (mq->mq_detached)
		{
			*bytes_written = sent;
			return SHM_MQ_DETACHED;
		}

		if (available == 0 && !mqh->mqh_counterparty_attached)
		{
			/*
			 * The queue is full, so if the receiver isn't yet known to be
			 * attached, we must wait for that to happen.
			 */
			if (nowait)
			{
				if (shm_mq_counterparty_gone(mq, mqh->mqh_handle))
				{
					*bytes_written = sent;
					return SHM_MQ_DETACHED;
				}
				if (shm_mq_get_receiver(mq) == NULL)
				{
					*bytes_written = sent;
					return SHM_MQ_WOULD_BLOCK;
				}
			}
			else if (!shm_mq_wait_internal(mq, &mq->mq_receiver,
										   mqh->mqh_handle))
			{
				mq->mq_detached = true;
				*bytes_written = sent;
				return SHM_MQ_DETACHED;
			}
			mqh->mqh_counterparty_attached = true;

			/*
			 * The receiver may have read some data after attaching, so we
			 * must not wait without rechecking the queue state.
			 */
		}
		else if (available == 0)
		{
			/*
			 * Since mq->mqh_counterparty_attached is known to be true at this
			 * point, mq_receiver has been set, and it can't change once set.
			 * Therefore, we can read it without acquiring the spinlock.
			 */
			Assert(mqh->mqh_counterparty_attached);
			SetLatch(&mq->mq_receiver->procLatch);

			/* Skip manipulation of our latch if nowait = true. */
			if (nowait)
			{
				*bytes_written = sent;
				return SHM_MQ_WOULD_BLOCK;
			}

			/*
			 * Wait for our latch to be set.  It might already be set for some
			 * unrelated reason, but that'll just result in one extra trip
			 * through the loop.  It's worth it to avoid resetting the latch
			 * at top of loop, because setting an already-set latch is much
			 * cheaper than setting one that has been reset.
			 */
			(void) WaitLatch(MyLatch, WL_LATCH_SET | WL_EXIT_ON_PM_DEATH, 0,
							 WAIT_EVENT_MQ_SEND);

			/* Reset the latch so we don't spin. */
			ResetLatch(MyLatch);

			/* An interrupt may have occurred while we were waiting. */
			CHECK_FOR_INTERRUPTS();
		}
		else
		{
			Size		offset;
			Size		sendnow;

			offset = wb % (uint64) ringsize;
			sendnow = Min(available, ringsize - offset);

			/*
			 * Write as much data as we can via a single memcpy(). Make sure
			 * these writes happen after the read of mq_bytes_read, above.
			 * This barrier pairs with the one in shm_mq_inc_bytes_read.
			 * (Since we're separating the read of mq_bytes_read from a
			 * subsequent write to mq_ring, we need a full barrier here.)
			 */
			pg_memory_barrier();
			memcpy(&mq->mq_ring[mq->mq_ring_offset + offset],
				   (char *) data + sent, sendnow);
			sent += sendnow;

			/*
			 * Update count of bytes written, with alignment padding.  Note
			 * that this will never actually insert any padding except at the
			 * end of a run of bytes, because the buffer size is a multiple of
			 * MAXIMUM_ALIGNOF, and each read is as well.
			 */
			Assert(sent == nbytes || sendnow == MAXALIGN(sendnow));
			shm_mq_inc_bytes_written(mq, MAXALIGN(sendnow));

			/*
			 * For efficiency, we don't set the reader's latch here.  We'll do
			 * that only when the buffer fills up or after writing an entire
			 * message.
			 */
		}
	}

	*bytes_written = sent;
	return SHM_MQ_SUCCESS;
}