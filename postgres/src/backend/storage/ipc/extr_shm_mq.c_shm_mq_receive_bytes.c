#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  shm_mq_result ;
struct TYPE_5__ {scalar_t__ mqh_consume_pending; TYPE_2__* mqh_queue; } ;
typedef  TYPE_1__ shm_mq_handle ;
struct TYPE_6__ {scalar_t__ mq_ring_size; scalar_t__ mq_ring_offset; int /*<<< orphan*/  mq_bytes_written; scalar_t__ mq_detached; int /*<<< orphan*/ * mq_ring; int /*<<< orphan*/  mq_bytes_read; } ;
typedef  TYPE_2__ shm_mq ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ Min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHM_MQ_DETACHED ; 
 int /*<<< orphan*/  SHM_MQ_SUCCESS ; 
 int /*<<< orphan*/  SHM_MQ_WOULD_BLOCK ; 
 int /*<<< orphan*/  WAIT_EVENT_MQ_RECEIVE ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_atomic_read_u64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_read_barrier () ; 
 int /*<<< orphan*/  shm_mq_inc_bytes_read (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static shm_mq_result
shm_mq_receive_bytes(shm_mq_handle *mqh, Size bytes_needed, bool nowait,
					 Size *nbytesp, void **datap)
{
	shm_mq	   *mq = mqh->mqh_queue;
	Size		ringsize = mq->mq_ring_size;
	uint64		used;
	uint64		written;

	for (;;)
	{
		Size		offset;
		uint64		read;

		/* Get bytes written, so we can compute what's available to read. */
		written = pg_atomic_read_u64(&mq->mq_bytes_written);

		/*
		 * Get bytes read.  Include bytes we could consume but have not yet
		 * consumed.
		 */
		read = pg_atomic_read_u64(&mq->mq_bytes_read) +
			mqh->mqh_consume_pending;
		used = written - read;
		Assert(used <= ringsize);
		offset = read % (uint64) ringsize;

		/* If we have enough data or buffer has wrapped, we're done. */
		if (used >= bytes_needed || offset + used >= ringsize)
		{
			*nbytesp = Min(used, ringsize - offset);
			*datap = &mq->mq_ring[mq->mq_ring_offset + offset];

			/*
			 * Separate the read of mq_bytes_written, above, from caller's
			 * attempt to read the data itself.  Pairs with the barrier in
			 * shm_mq_inc_bytes_written.
			 */
			pg_read_barrier();
			return SHM_MQ_SUCCESS;
		}

		/*
		 * Fall out before waiting if the queue has been detached.
		 *
		 * Note that we don't check for this until *after* considering whether
		 * the data already available is enough, since the receiver can finish
		 * receiving a message stored in the buffer even after the sender has
		 * detached.
		 */
		if (mq->mq_detached)
		{
			/*
			 * If the writer advanced mq_bytes_written and then set
			 * mq_detached, we might not have read the final value of
			 * mq_bytes_written above.  Insert a read barrier and then check
			 * again if mq_bytes_written has advanced.
			 */
			pg_read_barrier();
			if (written != pg_atomic_read_u64(&mq->mq_bytes_written))
				continue;

			return SHM_MQ_DETACHED;
		}

		/*
		 * We didn't get enough data to satisfy the request, so mark any data
		 * previously-consumed as read to make more buffer space.
		 */
		if (mqh->mqh_consume_pending > 0)
		{
			shm_mq_inc_bytes_read(mq, mqh->mqh_consume_pending);
			mqh->mqh_consume_pending = 0;
		}

		/* Skip manipulation of our latch if nowait = true. */
		if (nowait)
			return SHM_MQ_WOULD_BLOCK;

		/*
		 * Wait for our latch to be set.  It might already be set for some
		 * unrelated reason, but that'll just result in one extra trip through
		 * the loop.  It's worth it to avoid resetting the latch at top of
		 * loop, because setting an already-set latch is much cheaper than
		 * setting one that has been reset.
		 */
		(void) WaitLatch(MyLatch, WL_LATCH_SET | WL_EXIT_ON_PM_DEATH, 0,
						 WAIT_EVENT_MQ_RECEIVE);

		/* Reset the latch so we don't spin. */
		ResetLatch(MyLatch);

		/* An interrupt may have occurred while we were waiting. */
		CHECK_FOR_INTERRUPTS();
	}
}