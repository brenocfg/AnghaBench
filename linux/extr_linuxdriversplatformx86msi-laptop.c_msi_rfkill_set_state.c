#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rfkill {int dummy; } ;
struct TYPE_2__ {scalar_t__ ec_read_only; } ;

/* Variables and functions */
 TYPE_1__* quirks ; 
 int rfkill_set_hw_state (struct rfkill*,int) ; 
 int rfkill_set_sw_state (struct rfkill*,int) ; 

__attribute__((used)) static bool msi_rfkill_set_state(struct rfkill *rfkill, bool blocked)
{
	if (quirks->ec_read_only)
		return rfkill_set_hw_state(rfkill, blocked);
	else
		return rfkill_set_sw_state(rfkill, blocked);
}