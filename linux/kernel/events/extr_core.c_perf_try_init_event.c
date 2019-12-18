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
struct pmu {scalar_t__ task_ctx_nr; int (* event_init ) (struct perf_event*) ;int capabilities; int /*<<< orphan*/  module; } ;
struct perf_event_context {int dummy; } ;
struct perf_event {int /*<<< orphan*/  (* destroy ) (struct perf_event*) ;struct perf_event* group_leader; struct pmu* pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int PERF_PMU_CAP_EXTENDED_REGS ; 
 int PERF_PMU_CAP_NO_EXCLUDE ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 scalar_t__ event_has_any_exclude_flag (struct perf_event*) ; 
 scalar_t__ has_extended_regs (struct perf_event*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct perf_event_context* perf_event_ctx_lock_nested (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_ctx_unlock (struct perf_event*,struct perf_event_context*) ; 
 scalar_t__ perf_sw_context ; 
 int stub1 (struct perf_event*) ; 
 int /*<<< orphan*/  stub2 (struct perf_event*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_try_init_event(struct pmu *pmu, struct perf_event *event)
{
	struct perf_event_context *ctx = NULL;
	int ret;

	if (!try_module_get(pmu->module))
		return -ENODEV;

	/*
	 * A number of pmu->event_init() methods iterate the sibling_list to,
	 * for example, validate if the group fits on the PMU. Therefore,
	 * if this is a sibling event, acquire the ctx->mutex to protect
	 * the sibling_list.
	 */
	if (event->group_leader != event && pmu->task_ctx_nr != perf_sw_context) {
		/*
		 * This ctx->mutex can nest when we're called through
		 * inheritance. See the perf_event_ctx_lock_nested() comment.
		 */
		ctx = perf_event_ctx_lock_nested(event->group_leader,
						 SINGLE_DEPTH_NESTING);
		BUG_ON(!ctx);
	}

	event->pmu = pmu;
	ret = pmu->event_init(event);

	if (ctx)
		perf_event_ctx_unlock(event->group_leader, ctx);

	if (!ret) {
		if (!(pmu->capabilities & PERF_PMU_CAP_EXTENDED_REGS) &&
		    has_extended_regs(event))
			ret = -EOPNOTSUPP;

		if (pmu->capabilities & PERF_PMU_CAP_NO_EXCLUDE &&
		    event_has_any_exclude_flag(event))
			ret = -EINVAL;

		if (ret && event->destroy)
			event->destroy(event);
	}

	if (ret)
		module_put(pmu->module);

	return ret;
}