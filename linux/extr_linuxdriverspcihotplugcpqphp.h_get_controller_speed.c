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
typedef  int u8 ;
typedef  int u16 ;
struct controller {scalar_t__ hpc_reg; scalar_t__ pcix_support; } ;

/* Variables and functions */
 scalar_t__ MISC ; 
 scalar_t__ NEXT_CURR_FREQ ; 
 int PCI_SPEED_100MHz_PCIX ; 
 int PCI_SPEED_133MHz_PCIX ; 
 int PCI_SPEED_33MHz ; 
 int PCI_SPEED_66MHz ; 
 int PCI_SPEED_66MHz_PCIX ; 
 int readb (scalar_t__) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static inline u8 get_controller_speed(struct controller *ctrl)
{
	u8 curr_freq;
	u16 misc;

	if (ctrl->pcix_support) {
		curr_freq = readb(ctrl->hpc_reg + NEXT_CURR_FREQ);
		if ((curr_freq & 0xB0) == 0xB0)
			return PCI_SPEED_133MHz_PCIX;
		if ((curr_freq & 0xA0) == 0xA0)
			return PCI_SPEED_100MHz_PCIX;
		if ((curr_freq & 0x90) == 0x90)
			return PCI_SPEED_66MHz_PCIX;
		if (curr_freq & 0x10)
			return PCI_SPEED_66MHz;

		return PCI_SPEED_33MHz;
	}

	misc = readw(ctrl->hpc_reg + MISC);
	return (misc & 0x0800) ? PCI_SPEED_66MHz : PCI_SPEED_33MHz;
}