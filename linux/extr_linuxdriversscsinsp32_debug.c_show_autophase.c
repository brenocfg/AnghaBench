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
 unsigned short AUTOSCSI_BUSY ; 
 unsigned short BUS_FREE_OCCUER ; 
 unsigned short COMMAND_PHASE ; 
 unsigned short DATA_IN_PHASE ; 
 unsigned short DATA_OUT_PHASE ; 
 unsigned short ILLEGAL_PHASE ; 
 unsigned short MSGIN_00_VALID ; 
 unsigned short MSGIN_02_VALID ; 
 unsigned short MSGIN_03_VALID ; 
 unsigned short MSGIN_04_VALID ; 
 unsigned short MSGOUT_PHASE ; 
 unsigned short MSG_IN_OCCUER ; 
 unsigned short MSG_OUT_OCCUER ; 
 unsigned short SELECTION_TIMEOUT ; 
 unsigned short STATUS_PHASE ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void show_autophase(unsigned short i)
{
	printk("auto: 0x%x,", i);

	if(i & COMMAND_PHASE) {
		printk(" cmd");
	}
	if(i & DATA_IN_PHASE) {
		printk(" din");
	}
	if(i & DATA_OUT_PHASE) {
		printk(" dout");
	}
	if(i & MSGOUT_PHASE) {
		printk(" mout");
	}
	if(i & STATUS_PHASE) {
		printk(" stat");
	}
	if(i & ILLEGAL_PHASE) {
		printk(" ill");
	}
	if(i & BUS_FREE_OCCUER) {
		printk(" bfree-o");
	}
	if(i & MSG_IN_OCCUER) {
		printk(" min-o");
	}
	if(i & MSG_OUT_OCCUER) {
		printk(" mout-o");
	}
	if(i & SELECTION_TIMEOUT) {
		printk(" sel");
	}
	if(i & MSGIN_00_VALID) {
		printk(" m0");
	}
	if(i & MSGIN_02_VALID) {
		printk(" m2");
	}
	if(i & MSGIN_03_VALID) {
		printk(" m3");
	}
	if(i & MSGIN_04_VALID) {
		printk(" m4");
	}
	if(i & AUTOSCSI_BUSY) {
		printk(" busy");
	}

	printk("\n");
}