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
typedef  int /*<<< orphan*/  suspend_state_t ;
struct regulator_state {int /*<<< orphan*/  enabled; int /*<<< orphan*/  changeable; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_IN_SUSPEND ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENABLE_IN_SUSPEND ; 
 int EPERM ; 
 struct regulator_state* regulator_get_suspend_state (struct regulator_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int regulator_suspend_toggle(struct regulator_dev *rdev,
					   suspend_state_t state, bool en)
{
	struct regulator_state *rstate;

	rstate = regulator_get_suspend_state(rdev, state);
	if (rstate == NULL)
		return -EINVAL;

	if (!rstate->changeable)
		return -EPERM;

	rstate->enabled = (en) ? ENABLE_IN_SUSPEND : DISABLE_IN_SUSPEND;

	return 0;
}