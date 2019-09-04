#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hw; } ;
struct sum_mgr {TYPE_1__ mgr; } ;
struct sum_desc {int /*<<< orphan*/  msr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct sum {TYPE_2__ rsc; int /*<<< orphan*/ * idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUM ; 
 int rsc_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sum_basic_rsc_ops ; 

__attribute__((used)) static int sum_rsc_init(struct sum *sum,
			const struct sum_desc *desc,
			struct sum_mgr *mgr)
{
	int err;

	err = rsc_init(&sum->rsc, sum->idx[0], SUM, desc->msr, mgr->mgr.hw);
	if (err)
		return err;

	sum->rsc.ops = &sum_basic_rsc_ops;

	return 0;
}