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
struct btc_coexist {int auto_report_1ant; } ;

/* Variables and functions */
 int /*<<< orphan*/  btc8821a1ant_init_hw_config (struct btc_coexist*,int,int) ; 

void ex_btc8821a1ant_init_hwconfig(struct btc_coexist *btcoexist, bool wifionly)
{
	btc8821a1ant_init_hw_config(btcoexist, true, wifionly);
	btcoexist->auto_report_1ant = true;
}