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
struct hdspm {int control_register; } ;

/* Variables and functions */
 int HDSPM_DoubleSpeed ; 
 int HDSPM_QuadSpeed ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdspm_set_madi_speedmode(struct hdspm *hdspm, int mode)
{
	hdspm->control_register &= ~(HDSPM_DoubleSpeed | HDSPM_QuadSpeed);
	switch (mode) {
	case 0:
		break;
	case 1:
		hdspm->control_register |= HDSPM_DoubleSpeed;
		break;
	case 2:
		hdspm->control_register |= HDSPM_QuadSpeed;
		break;
	}
	hdspm_write(hdspm, HDSPM_controlRegister, hdspm->control_register);

	return 0;
}