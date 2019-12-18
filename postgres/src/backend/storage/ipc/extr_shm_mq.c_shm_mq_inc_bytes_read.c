#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* mq_sender; int /*<<< orphan*/  mq_bytes_read; } ;
typedef  TYPE_1__ shm_mq ;
struct TYPE_5__ {int /*<<< orphan*/  procLatch; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 scalar_t__ pg_atomic_read_u64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_atomic_write_u64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pg_read_barrier () ; 

__attribute__((used)) static void
shm_mq_inc_bytes_read(shm_mq *mq, Size n)
{
	PGPROC	   *sender;

	/*
	 * Separate prior reads of mq_ring from the increment of mq_bytes_read
	 * which follows.  This pairs with the full barrier in
	 * shm_mq_send_bytes(). We only need a read barrier here because the
	 * increment of mq_bytes_read is actually a read followed by a dependent
	 * write.
	 */
	pg_read_barrier();

	/*
	 * There's no need to use pg_atomic_fetch_add_u64 here, because nobody
	 * else can be changing this value.  This method should be cheaper.
	 */
	pg_atomic_write_u64(&mq->mq_bytes_read,
						pg_atomic_read_u64(&mq->mq_bytes_read) + n);

	/*
	 * We shouldn't have any bytes to read without a sender, so we can read
	 * mq_sender here without a lock.  Once it's initialized, it can't change.
	 */
	sender = mq->mq_sender;
	Assert(sender != NULL);
	SetLatch(&sender->procLatch);
}