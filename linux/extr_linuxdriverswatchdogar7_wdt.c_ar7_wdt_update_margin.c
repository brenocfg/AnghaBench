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

/* Variables and functions */
 int /*<<< orphan*/  ar7_wdt_change (int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int margin ; 
 int /*<<< orphan*/  pr_info (char*,int,int,int,int) ; 
 int prescale_value ; 
 int /*<<< orphan*/  vbus_clk ; 

__attribute__((used)) static void ar7_wdt_update_margin(int new_margin)
{
	u32 change;
	u32 vbus_rate;

	vbus_rate = clk_get_rate(vbus_clk);
	change = new_margin * (vbus_rate / prescale_value);
	if (change < 1)
		change = 1;
	if (change > 0xffff)
		change = 0xffff;
	ar7_wdt_change(change);
	margin = change * prescale_value / vbus_rate;
	pr_info("timer margin %d seconds (prescale %d, change %d, freq %d)\n",
		margin, prescale_value, change, vbus_rate);
}