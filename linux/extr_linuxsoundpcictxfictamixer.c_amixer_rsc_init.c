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
struct amixer_mgr {TYPE_1__ mgr; } ;
struct amixer_desc {int /*<<< orphan*/  msr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct amixer {int /*<<< orphan*/ * sum; int /*<<< orphan*/ * input; int /*<<< orphan*/ * ops; TYPE_2__ rsc; int /*<<< orphan*/ * idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMIXER ; 
 int /*<<< orphan*/  amixer_basic_rsc_ops ; 
 int /*<<< orphan*/  amixer_ops ; 
 int /*<<< orphan*/  amixer_setup (struct amixer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rsc_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amixer_rsc_init(struct amixer *amixer,
			   const struct amixer_desc *desc,
			   struct amixer_mgr *mgr)
{
	int err;

	err = rsc_init(&amixer->rsc, amixer->idx[0],
			AMIXER, desc->msr, mgr->mgr.hw);
	if (err)
		return err;

	/* Set amixer specific operations */
	amixer->rsc.ops = &amixer_basic_rsc_ops;
	amixer->ops = &amixer_ops;
	amixer->input = NULL;
	amixer->sum = NULL;

	amixer_setup(amixer, NULL, 0, NULL);

	return 0;
}