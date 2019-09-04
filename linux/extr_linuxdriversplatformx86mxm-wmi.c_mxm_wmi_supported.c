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

/* Variables and functions */
 int /*<<< orphan*/  MXM_WMMX_GUID ; 
 int wmi_has_guid (int /*<<< orphan*/ ) ; 

bool mxm_wmi_supported(void)
{
	bool guid_valid;
	guid_valid = wmi_has_guid(MXM_WMMX_GUID);
	return guid_valid;
}