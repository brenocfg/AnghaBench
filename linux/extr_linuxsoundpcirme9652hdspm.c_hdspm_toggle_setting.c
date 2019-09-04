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
typedef  int u32 ;
struct hdspm {int settings_register; int control_register; } ;

/* Variables and functions */
 scalar_t__ hdspm_is_raydat_or_aio (struct hdspm*) ; 

__attribute__((used)) static int hdspm_toggle_setting(struct hdspm *hdspm, u32 regmask)
{
	u32 reg;

	if (hdspm_is_raydat_or_aio(hdspm))
		reg = hdspm->settings_register;
	else
		reg = hdspm->control_register;

	return (reg & regmask) ? 1 : 0;
}