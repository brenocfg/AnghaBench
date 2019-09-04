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
#define  SMODE_HVD 130 
#define  SMODE_LVD 129 
#define  SMODE_SE 128 

__attribute__((used)) static char *sym_scsi_bus_mode(int mode)
{
	switch(mode) {
	case SMODE_HVD:	return "HVD";
	case SMODE_SE:	return "SE";
	case SMODE_LVD: return "LVD";
	}
	return "??";
}