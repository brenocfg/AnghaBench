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
struct printk_safe_seq_buf {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 scalar_t__ printk_safe_irq_ready ; 

__attribute__((used)) static void queue_flush_work(struct printk_safe_seq_buf *s)
{
	if (printk_safe_irq_ready)
		irq_work_queue(&s->work);
}