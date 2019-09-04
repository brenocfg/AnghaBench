#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  action; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRIVER_NAME_SHORT ; 
 int /*<<< orphan*/  pqi_lockup_action ; 
 int /*<<< orphan*/  pqi_lockup_action_param ; 
 TYPE_1__* pqi_lockup_actions ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_process_lockup_action_param(void)
{
	unsigned int i;

	if (!pqi_lockup_action_param)
		return;

	for (i = 0; i < ARRAY_SIZE(pqi_lockup_actions); i++) {
		if (strcmp(pqi_lockup_action_param,
			pqi_lockup_actions[i].name) == 0) {
			pqi_lockup_action = pqi_lockup_actions[i].action;
			return;
		}
	}

	pr_warn("%s: invalid lockup action setting \"%s\" - supported settings: none, reboot, panic\n",
		DRIVER_NAME_SHORT, pqi_lockup_action_param);
}