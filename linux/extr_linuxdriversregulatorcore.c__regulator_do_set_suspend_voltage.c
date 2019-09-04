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
typedef  int /*<<< orphan*/  suspend_state_t ;
struct regulator_state {int min_uV; int max_uV; int uV; } ;
struct regulator_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* list_voltage ) (struct regulator_dev*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct regulator_state* regulator_get_suspend_state (struct regulator_dev*,int /*<<< orphan*/ ) ; 
 int regulator_map_voltage (struct regulator_dev*,int,int) ; 
 int stub1 (struct regulator_dev*,int) ; 

__attribute__((used)) static int _regulator_do_set_suspend_voltage(struct regulator_dev *rdev,
				  int min_uV, int max_uV, suspend_state_t state)
{
	struct regulator_state *rstate;
	int uV, sel;

	rstate = regulator_get_suspend_state(rdev, state);
	if (rstate == NULL)
		return -EINVAL;

	if (min_uV < rstate->min_uV)
		min_uV = rstate->min_uV;
	if (max_uV > rstate->max_uV)
		max_uV = rstate->max_uV;

	sel = regulator_map_voltage(rdev, min_uV, max_uV);
	if (sel < 0)
		return sel;

	uV = rdev->desc->ops->list_voltage(rdev, sel);
	if (uV >= min_uV && uV <= max_uV)
		rstate->uV = uV;

	return 0;
}