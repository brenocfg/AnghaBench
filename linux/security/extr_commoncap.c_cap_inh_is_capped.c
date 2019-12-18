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
struct TYPE_3__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_OPT_NONE ; 
 int /*<<< orphan*/  CAP_SETPCAP ; 
 scalar_t__ cap_capable (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_cred () ; 

__attribute__((used)) static inline int cap_inh_is_capped(void)
{
	/* they are so limited unless the current task has the CAP_SETPCAP
	 * capability
	 */
	if (cap_capable(current_cred(), current_cred()->user_ns,
			CAP_SETPCAP, CAP_OPT_NONE) == 0)
		return 0;
	return 1;
}