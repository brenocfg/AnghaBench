#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tls_context {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tls_device_gc_list ; 
 int /*<<< orphan*/  tls_device_gc_work ; 
 int /*<<< orphan*/  tls_device_lock ; 

__attribute__((used)) static void tls_device_queue_ctx_destruction(struct tls_context *ctx)
{
	unsigned long flags;

	spin_lock_irqsave(&tls_device_lock, flags);
	list_move_tail(&ctx->list, &tls_device_gc_list);

	/* schedule_work inside the spinlock
	 * to make sure tls_device_down waits for that work.
	 */
	schedule_work(&tls_device_gc_work);

	spin_unlock_irqrestore(&tls_device_lock, flags);
}