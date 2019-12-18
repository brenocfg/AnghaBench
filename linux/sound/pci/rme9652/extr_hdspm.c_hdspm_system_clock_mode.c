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
struct hdspm {int io_type; int settings_register; int control_register; } ;

/* Variables and functions */
#define  AIO 129 
 int HDSPM_ClockModeMaster ; 
 int HDSPM_c0Master ; 
#define  RayDAT 128 

__attribute__((used)) static int hdspm_system_clock_mode(struct hdspm *hdspm)
{
	switch (hdspm->io_type) {
	case AIO:
	case RayDAT:
		if (hdspm->settings_register & HDSPM_c0Master)
			return 0;
		break;

	default:
		if (hdspm->control_register & HDSPM_ClockModeMaster)
			return 0;
	}

	return 1;
}