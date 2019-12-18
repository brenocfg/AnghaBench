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
struct perf_event_context {scalar_t__ generation; scalar_t__ parent_gen; struct perf_event_context* parent_ctx; scalar_t__ pin_count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int context_equiv(struct perf_event_context *ctx1,
			 struct perf_event_context *ctx2)
{
	lockdep_assert_held(&ctx1->lock);
	lockdep_assert_held(&ctx2->lock);

	/* Pinning disables the swap optimization */
	if (ctx1->pin_count || ctx2->pin_count)
		return 0;

	/* If ctx1 is the parent of ctx2 */
	if (ctx1 == ctx2->parent_ctx && ctx1->generation == ctx2->parent_gen)
		return 1;

	/* If ctx2 is the parent of ctx1 */
	if (ctx1->parent_ctx == ctx2 && ctx1->parent_gen == ctx2->generation)
		return 1;

	/*
	 * If ctx1 and ctx2 have the same parent; we flatten the parent
	 * hierarchy, see perf_event_init_context().
	 */
	if (ctx1->parent_ctx && ctx1->parent_ctx == ctx2->parent_ctx &&
			ctx1->parent_gen == ctx2->parent_gen)
		return 1;

	/* Unmatched */
	return 0;
}