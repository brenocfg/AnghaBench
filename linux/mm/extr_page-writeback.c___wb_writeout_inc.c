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
struct wb_domain {int dummy; } ;
struct bdi_writeback {TYPE_1__* bdi; int /*<<< orphan*/  completions; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_prop_frac; } ;

/* Variables and functions */
 int /*<<< orphan*/  WB_WRITTEN ; 
 struct wb_domain global_wb_domain ; 
 int /*<<< orphan*/  inc_wb_stat (struct bdi_writeback*,int /*<<< orphan*/ ) ; 
 struct wb_domain* mem_cgroup_wb_domain (struct bdi_writeback*) ; 
 int /*<<< orphan*/  wb_domain_writeout_inc (struct wb_domain*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wb_memcg_completions (struct bdi_writeback*) ; 

__attribute__((used)) static inline void __wb_writeout_inc(struct bdi_writeback *wb)
{
	struct wb_domain *cgdom;

	inc_wb_stat(wb, WB_WRITTEN);
	wb_domain_writeout_inc(&global_wb_domain, &wb->completions,
			       wb->bdi->max_prop_frac);

	cgdom = mem_cgroup_wb_domain(wb);
	if (cgdom)
		wb_domain_writeout_inc(cgdom, wb_memcg_completions(wb),
				       wb->bdi->max_prop_frac);
}