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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  reg_check_channels () ; 
 int /*<<< orphan*/  reg_indoor_lock ; 
 int reg_is_indoor ; 
 scalar_t__ reg_is_indoor_portid ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int regulatory_hint_indoor(bool is_indoor, u32 portid)
{
	spin_lock(&reg_indoor_lock);

	/* It is possible that more than one user space process is trying to
	 * configure the indoor setting. To handle such cases, clear the indoor
	 * setting in case that some process does not think that the device
	 * is operating in an indoor environment. In addition, if a user space
	 * process indicates that it is controlling the indoor setting, save its
	 * portid, i.e., make it the owner.
	 */
	reg_is_indoor = is_indoor;
	if (reg_is_indoor) {
		if (!reg_is_indoor_portid)
			reg_is_indoor_portid = portid;
	} else {
		reg_is_indoor_portid = 0;
	}

	spin_unlock(&reg_indoor_lock);

	if (!is_indoor)
		reg_check_channels();

	return 0;
}