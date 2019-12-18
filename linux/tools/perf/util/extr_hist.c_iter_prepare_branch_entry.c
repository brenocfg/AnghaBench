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
struct perf_sample {TYPE_1__* branch_stack; } ;
struct hist_entry_iter {struct branch_info* priv; int /*<<< orphan*/  total; scalar_t__ curr; struct perf_sample* sample; } ;
struct branch_info {int dummy; } ;
struct addr_location {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct branch_info* sample__resolve_bstack (struct perf_sample*,struct addr_location*) ; 

__attribute__((used)) static int
iter_prepare_branch_entry(struct hist_entry_iter *iter, struct addr_location *al)
{
	struct branch_info *bi;
	struct perf_sample *sample = iter->sample;

	bi = sample__resolve_bstack(sample, al);
	if (!bi)
		return -ENOMEM;

	iter->curr = 0;
	iter->total = sample->branch_stack->nr;

	iter->priv = bi;
	return 0;
}