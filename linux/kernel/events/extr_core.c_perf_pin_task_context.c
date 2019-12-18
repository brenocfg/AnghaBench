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
struct task_struct {int dummy; } ;
struct perf_event_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  pin_count; } ;

/* Variables and functions */
 struct perf_event_context* perf_lock_task_context (struct task_struct*,int,unsigned long*) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct perf_event_context *
perf_pin_task_context(struct task_struct *task, int ctxn)
{
	struct perf_event_context *ctx;
	unsigned long flags;

	ctx = perf_lock_task_context(task, ctxn, &flags);
	if (ctx) {
		++ctx->pin_count;
		raw_spin_unlock_irqrestore(&ctx->lock, flags);
	}
	return ctx;
}