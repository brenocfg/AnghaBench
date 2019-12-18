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
 int HDSPM_QS_DoubleWire ; 
 int HDSPM_QS_QuadWire ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdspm_set_qs_wire(struct hdspm * hdspm, int mode)
{
	hdspm->control_register &= ~(HDSPM_QS_DoubleWire | HDSPM_QS_QuadWire);
	switch (mode) {
	case 0:
		break;
	case 1:
		hdspm->control_register |= HDSPM_QS_DoubleWire;
		break;
	case 2:
		hdspm->control_register |= HDSPM_QS_QuadWire;
		break;
	}
	hdspm_write(hdspm, HDSPM_controlRegister, hdspm->control_register);

	return 0;
}