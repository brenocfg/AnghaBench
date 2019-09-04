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

__attribute__((used)) static unsigned char control_pc_to_mfc3(unsigned char control)
{
	unsigned char ret = 32|64;

	if (control & PARPORT_CONTROL_SELECT) /* XXX: What is SELECP? */
		ret &= ~32; /* /SELECT_IN */
	if (control & PARPORT_CONTROL_INIT) /* INITP */
		ret |= 128;
	if (control & PARPORT_CONTROL_AUTOFD) /* AUTOLF */
		ret &= ~64;
	if (control & PARPORT_CONTROL_STROBE) /* Strobe */
		/* Handled directly by hardware */;
	return ret;
}