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
struct btc_coexist {int auto_report_2ant; } ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc8822b2ant_init_hw_config (struct btc_coexist*,int) ; 

void ex_btc8822b2ant_init_hw_config(struct btc_coexist *btcoexist,
				    bool wifi_only)
{
	halbtc8822b2ant_init_hw_config(btcoexist, wifi_only);
	btcoexist->auto_report_2ant = true;
}