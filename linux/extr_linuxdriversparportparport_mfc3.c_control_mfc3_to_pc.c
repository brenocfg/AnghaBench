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
 unsigned char PARPORT_CONTROL_AUTOFD ; 
 unsigned char PARPORT_CONTROL_INIT ; 
 unsigned char PARPORT_CONTROL_SELECT ; 
 unsigned char PARPORT_CONTROL_STROBE ; 

__attribute__((used)) static unsigned char control_mfc3_to_pc(unsigned char control)
{
	unsigned char ret = PARPORT_CONTROL_STROBE 
			  | PARPORT_CONTROL_AUTOFD | PARPORT_CONTROL_SELECT;

	if (control & 128) /* /INITP */
		ret |= PARPORT_CONTROL_INIT;
	if (control & 64) /* /AUTOLF */
		ret &= ~PARPORT_CONTROL_AUTOFD;
	if (control & 32) /* /SELECT_IN */
		ret &= ~PARPORT_CONTROL_SELECT;
	return ret;
}