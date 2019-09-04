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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_METHODID_DEVS ; 
 int asus_wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_wmi_set_devstate(u32 dev_id, u32 ctrl_param,
				 u32 *retval)
{
	return asus_wmi_evaluate_method(ASUS_WMI_METHODID_DEVS, dev_id,
					ctrl_param, retval);
}