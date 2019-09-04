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
typedef  enum hp_wmi_radio { ____Placeholder_hp_wmi_radio } hp_wmi_radio ;

/* Variables and functions */
 int /*<<< orphan*/  HPWMI_WIRELESS_QUERY ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int hp_wmi_read_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hp_wmi_get_hw_state(enum hp_wmi_radio r)
{
	int mask = 0x800 << (r * 8);

	int wireless = hp_wmi_read_int(HPWMI_WIRELESS_QUERY);

	/* TBD: Pass error */
	WARN_ONCE(wireless < 0, "error executing HPWMI_WIRELESS_QUERY");

	return !(wireless & mask);
}