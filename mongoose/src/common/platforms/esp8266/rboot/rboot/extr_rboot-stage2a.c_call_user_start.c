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
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */

void call_user_start(uint32 readpos) {
	__asm volatile (
		"mov a15, a0\n"     // store return addr, we already splatted a15!
		"call0 load_rom\n"  // load the rom
		"mov a0, a15\n"     // restore return addr
		"jx a2\n"           // now jump to the rom code
	);
}