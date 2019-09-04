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
struct net_device {int dummy; } ;
struct TYPE_2__ {int dig_enable_flag; scalar_t__ dig_algorithm; } ;

/* Variables and functions */
 scalar_t__ DIG_ALGO_BY_FALSE_ALARM ; 
 scalar_t__ DIG_ALGO_BY_RSSI ; 
 int /*<<< orphan*/  _rtl92e_dm_ctrl_initgain_byrssi_driver (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_dm_ctrl_initgain_byrssi_false_alarm (struct net_device*) ; 
 TYPE_1__ dm_digtable ; 

__attribute__((used)) static void _rtl92e_dm_ctrl_initgain_byrssi(struct net_device *dev)
{

	if (dm_digtable.dig_enable_flag == false)
		return;

	if (dm_digtable.dig_algorithm == DIG_ALGO_BY_FALSE_ALARM)
		_rtl92e_dm_ctrl_initgain_byrssi_false_alarm(dev);
	else if (dm_digtable.dig_algorithm == DIG_ALGO_BY_RSSI)
		_rtl92e_dm_ctrl_initgain_byrssi_driver(dev);
	else
		return;
}