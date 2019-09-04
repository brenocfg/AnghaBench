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
struct TYPE_2__ {int bt_disable_low_pwr; } ;
struct btc_coexist {TYPE_1__ bt_info; } ;

/* Variables and functions */

__attribute__((used)) static void halbtc_disable_low_power(struct btc_coexist *btcoexist,
				     bool low_pwr_disable)
{
	/* TODO: original/leave 32k low power */
	btcoexist->bt_info.bt_disable_low_pwr = low_pwr_disable;
}