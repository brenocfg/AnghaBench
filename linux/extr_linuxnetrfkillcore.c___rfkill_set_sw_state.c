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
typedef  int u32 ;
struct rfkill {int state; } ;

/* Variables and functions */
 int RFKILL_BLOCK_SW ; 
 int RFKILL_BLOCK_SW_PREV ; 
 int RFKILL_BLOCK_SW_SETCALL ; 

__attribute__((used)) static void __rfkill_set_sw_state(struct rfkill *rfkill, bool blocked)
{
	u32 bit = RFKILL_BLOCK_SW;

	/* if in a ops->set_block right now, use other bit */
	if (rfkill->state & RFKILL_BLOCK_SW_SETCALL)
		bit = RFKILL_BLOCK_SW_PREV;

	if (blocked)
		rfkill->state |= bit;
	else
		rfkill->state &= ~bit;
}