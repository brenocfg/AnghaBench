#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer {int /*<<< orphan*/  wakeup; int /*<<< orphan*/  nest; int /*<<< orphan*/  head; TYPE_1__* user_page; } ;
struct perf_output_handle {unsigned long wakeup; struct ring_buffer* rb; } ;
struct TYPE_2__ {unsigned long data_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_inc (int /*<<< orphan*/ *) ; 
 unsigned long local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_output_wakeup (struct perf_output_handle*) ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void perf_output_put_handle(struct perf_output_handle *handle)
{
	struct ring_buffer *rb = handle->rb;
	unsigned long head;

again:
	head = local_read(&rb->head);

	/*
	 * IRQ/NMI can happen here, which means we can miss a head update.
	 */

	if (!local_dec_and_test(&rb->nest))
		goto out;

	/*
	 * Since the mmap() consumer (userspace) can run on a different CPU:
	 *
	 *   kernel				user
	 *
	 *   if (LOAD ->data_tail) {		LOAD ->data_head
	 *			(A)		smp_rmb()	(C)
	 *	STORE $data			LOAD $data
	 *	smp_wmb()	(B)		smp_mb()	(D)
	 *	STORE ->data_head		STORE ->data_tail
	 *   }
	 *
	 * Where A pairs with D, and B pairs with C.
	 *
	 * In our case (A) is a control dependency that separates the load of
	 * the ->data_tail and the stores of $data. In case ->data_tail
	 * indicates there is no room in the buffer to store $data we do not.
	 *
	 * D needs to be a full barrier since it separates the data READ
	 * from the tail WRITE.
	 *
	 * For B a WMB is sufficient since it separates two WRITEs, and for C
	 * an RMB is sufficient since it separates two READs.
	 *
	 * See perf_output_begin().
	 */
	smp_wmb(); /* B, matches C */
	rb->user_page->data_head = head;

	/*
	 * Now check if we missed an update -- rely on previous implied
	 * compiler barriers to force a re-read.
	 */
	if (unlikely(head != local_read(&rb->head))) {
		local_inc(&rb->nest);
		goto again;
	}

	if (handle->wakeup != local_read(&rb->wakeup))
		perf_output_wakeup(handle);

out:
	preempt_enable();
}