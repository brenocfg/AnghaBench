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
struct b43legacy_phy {int txctl2; int* nrssi; int* nrssi_lt; int lofcal; int initval; int aci_enable; int aci_wlan_automatic; int aci_hw_rssi; int antenna_diversity; scalar_t__ loopback_gain; scalar_t__ _lo_pairs; scalar_t__ calibrated; scalar_t__ minlowsigpos; scalar_t__ minlowsig; scalar_t__ nrssislope; scalar_t__ txpwr_offset; int /*<<< orphan*/  txctl1; int /*<<< orphan*/  rfatt; int /*<<< orphan*/  bbatt; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;
struct b43legacy_lopair {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int B43legacy_LO_COUNT ; 
 int /*<<< orphan*/  b43legacy_default_baseband_attenuation (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_default_radio_attenuation (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_default_txctl1 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

__attribute__((used)) static void prepare_phy_data_for_init(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	int i;

	/* Set default attenuation values. */
	phy->bbatt = b43legacy_default_baseband_attenuation(dev);
	phy->rfatt = b43legacy_default_radio_attenuation(dev);
	phy->txctl1 = b43legacy_default_txctl1(dev);
	phy->txctl2 = 0xFFFF;
	phy->txpwr_offset = 0;

	/* NRSSI */
	phy->nrssislope = 0;
	for (i = 0; i < ARRAY_SIZE(phy->nrssi); i++)
		phy->nrssi[i] = -1000;
	for (i = 0; i < ARRAY_SIZE(phy->nrssi_lt); i++)
		phy->nrssi_lt[i] = i;

	phy->lofcal = 0xFFFF;
	phy->initval = 0xFFFF;

	phy->aci_enable = false;
	phy->aci_wlan_automatic = false;
	phy->aci_hw_rssi = false;

	phy->antenna_diversity = 0xFFFF;
	memset(phy->minlowsig, 0xFF, sizeof(phy->minlowsig));
	memset(phy->minlowsigpos, 0, sizeof(phy->minlowsigpos));

	/* Flags */
	phy->calibrated = 0;

	if (phy->_lo_pairs)
		memset(phy->_lo_pairs, 0,
		       sizeof(struct b43legacy_lopair) * B43legacy_LO_COUNT);
	memset(phy->loopback_gain, 0, sizeof(phy->loopback_gain));
}