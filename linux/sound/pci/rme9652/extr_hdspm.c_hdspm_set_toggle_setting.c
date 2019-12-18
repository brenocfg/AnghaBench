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
struct hdspm {int /*<<< orphan*/  control_register; int /*<<< orphan*/  settings_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_WR_SETTINGS ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 scalar_t__ hdspm_is_raydat_or_aio (struct hdspm*) ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_set_toggle_setting(struct hdspm *hdspm, u32 regmask, int out)
{
	u32 *reg;
	u32 target_reg;

	if (hdspm_is_raydat_or_aio(hdspm)) {
		reg = &(hdspm->settings_register);
		target_reg = HDSPM_WR_SETTINGS;
	} else {
		reg = &(hdspm->control_register);
		target_reg = HDSPM_controlRegister;
	}

	if (out)
		*reg |= regmask;
	else
		*reg &= ~regmask;

	hdspm_write(hdspm, target_reg, *reg);

	return 0;
}