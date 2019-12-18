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
struct hdspm {int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_DS_DoubleWire ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_set_ds_wire(struct hdspm * hdspm, int ds)
{
	if (ds)
		hdspm->control_register |= HDSPM_DS_DoubleWire;
	else
		hdspm->control_register &= ~HDSPM_DS_DoubleWire;
	hdspm_write(hdspm, HDSPM_controlRegister, hdspm->control_register);

	return 0;
}