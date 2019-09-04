#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rt2x00lib_erp {int /*<<< orphan*/  ht_opmode; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  basic_rates; int /*<<< orphan*/  eifs; int /*<<< orphan*/  difs; int /*<<< orphan*/  pifs; int /*<<< orphan*/  sifs; int /*<<< orphan*/  slot_time; int /*<<< orphan*/  cts_protection; int /*<<< orphan*/  short_preamble; } ;
struct rt2x00_intf {int dummy; } ;
struct rt2x00_dev {TYPE_2__* ops; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  last_beacon; int /*<<< orphan*/  aid; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  ht_operation_mode; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  sync_tsf; int /*<<< orphan*/  aid; scalar_t__ assoc; int /*<<< orphan*/  basic_rates; scalar_t__ use_short_slot; int /*<<< orphan*/  use_cts_prot; int /*<<< orphan*/  use_short_preamble; } ;
typedef  int /*<<< orphan*/  erp ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* config_erp ) (struct rt2x00_dev*,struct rt2x00lib_erp*,int) ;} ;

/* Variables and functions */
 int BSS_CHANGED_HT ; 
 int /*<<< orphan*/  DIFS ; 
 int /*<<< orphan*/  EIFS ; 
 int /*<<< orphan*/  PIFS ; 
 int /*<<< orphan*/  SHORT_DIFS ; 
 int /*<<< orphan*/  SHORT_EIFS ; 
 int /*<<< orphan*/  SHORT_PIFS ; 
 int /*<<< orphan*/  SHORT_SLOT_TIME ; 
 int /*<<< orphan*/  SIFS ; 
 int /*<<< orphan*/  SLOT_TIME ; 
 int /*<<< orphan*/  memset (struct rt2x00lib_erp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,struct rt2x00lib_erp*,int) ; 

void rt2x00lib_config_erp(struct rt2x00_dev *rt2x00dev,
			  struct rt2x00_intf *intf,
			  struct ieee80211_bss_conf *bss_conf,
			  u32 changed)
{
	struct rt2x00lib_erp erp;

	memset(&erp, 0, sizeof(erp));

	erp.short_preamble = bss_conf->use_short_preamble;
	erp.cts_protection = bss_conf->use_cts_prot;

	erp.slot_time = bss_conf->use_short_slot ? SHORT_SLOT_TIME : SLOT_TIME;
	erp.sifs = SIFS;
	erp.pifs = bss_conf->use_short_slot ? SHORT_PIFS : PIFS;
	erp.difs = bss_conf->use_short_slot ? SHORT_DIFS : DIFS;
	erp.eifs = bss_conf->use_short_slot ? SHORT_EIFS : EIFS;

	erp.basic_rates = bss_conf->basic_rates;
	erp.beacon_int = bss_conf->beacon_int;

	/* Update the AID, this is needed for dynamic PS support */
	rt2x00dev->aid = bss_conf->assoc ? bss_conf->aid : 0;
	rt2x00dev->last_beacon = bss_conf->sync_tsf;

	/* Update global beacon interval time, this is needed for PS support */
	rt2x00dev->beacon_int = bss_conf->beacon_int;

	if (changed & BSS_CHANGED_HT)
		erp.ht_opmode = bss_conf->ht_operation_mode;

	rt2x00dev->ops->lib->config_erp(rt2x00dev, &erp, changed);
}