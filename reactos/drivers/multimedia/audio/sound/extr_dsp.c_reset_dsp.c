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
typedef  int /*<<< orphan*/  sb_status ;

/* Variables and functions */
 int /*<<< orphan*/  SB_TRUE ; 

sb_status reset_dsp(unsigned short base_address)
{
//	int delay;

//	outb(base_address+DSP_RESET_PORT,1);
//	for(delay=0;delay<0xffff;delay++);

//	outb(base_address+DSP_RESET_PORT,0);
//	for(delay=0;delay<0xffff;delay++);

//	if((inb(base_address+DSP_READ_STATUS_PORT)&0x80)==0) return SB_FALSE;

//	if(inb(base_address+DSP_READ_DATA_PORT)!=0xAA) return SB_FALSE;

	return SB_TRUE;
}