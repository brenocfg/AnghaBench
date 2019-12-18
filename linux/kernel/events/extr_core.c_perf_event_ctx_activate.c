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
struct perf_event_context {int /*<<< orphan*/  active_ctx_list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  active_ctx_list ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 struct list_head* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_event_ctx_activate(struct perf_event_context *ctx)
{
	struct list_head *head = this_cpu_ptr(&active_ctx_list);

	lockdep_assert_irqs_disabled();

	WARN_ON(!list_empty(&ctx->active_ctx_list));

	list_add(&ctx->active_ctx_list, head);
}