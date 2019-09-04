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
struct zd_rf {int patch_cck_gain; int /*<<< orphan*/  patch_6m_band_edge; int /*<<< orphan*/  switch_radio_on; int /*<<< orphan*/  set_channel; int /*<<< orphan*/  init_hw; int /*<<< orphan*/  switch_radio_off; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  al2230_switch_radio_off ; 
 int /*<<< orphan*/  zd1211_al2230_init_hw ; 
 int /*<<< orphan*/  zd1211_al2230_set_channel ; 
 int /*<<< orphan*/  zd1211_al2230_switch_radio_on ; 
 int /*<<< orphan*/  zd1211b_al2230_init_hw ; 
 int /*<<< orphan*/  zd1211b_al2230_set_channel ; 
 int /*<<< orphan*/  zd1211b_al2230_switch_radio_on ; 
 scalar_t__ zd_chip_is_zd1211b (struct zd_chip*) ; 
 int /*<<< orphan*/  zd_rf_generic_patch_6m ; 
 struct zd_chip* zd_rf_to_chip (struct zd_rf*) ; 

int zd_rf_init_al2230(struct zd_rf *rf)
{
	struct zd_chip *chip = zd_rf_to_chip(rf);

	rf->switch_radio_off = al2230_switch_radio_off;
	if (zd_chip_is_zd1211b(chip)) {
		rf->init_hw = zd1211b_al2230_init_hw;
		rf->set_channel = zd1211b_al2230_set_channel;
		rf->switch_radio_on = zd1211b_al2230_switch_radio_on;
	} else {
		rf->init_hw = zd1211_al2230_init_hw;
		rf->set_channel = zd1211_al2230_set_channel;
		rf->switch_radio_on = zd1211_al2230_switch_radio_on;
	}
	rf->patch_6m_band_edge = zd_rf_generic_patch_6m;
	rf->patch_cck_gain = 1;
	return 0;
}