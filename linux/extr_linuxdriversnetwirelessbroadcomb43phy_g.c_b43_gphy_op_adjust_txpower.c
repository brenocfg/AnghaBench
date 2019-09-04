#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct b43_phy {int radio_ver; int radio_rev; struct b43_phy_g* g; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_2__* dev; struct b43_phy phy; } ;
struct TYPE_8__ {int att; } ;
struct TYPE_7__ {int att; } ;
struct b43_phy_g {int tx_control; TYPE_4__ rfatt; TYPE_3__ bbatt; scalar_t__ rfatt_delta; scalar_t__ bbatt_delta; } ;
struct TYPE_6__ {TYPE_1__* bus_sprom; } ;
struct TYPE_5__ {int boardflags_lo; } ;

/* Variables and functions */
 int B43_BFL_PACTRL ; 
 int /*<<< orphan*/  B43_DBG_XMITPOWER ; 
 int B43_TXCTL_PA2DB ; 
 int B43_TXCTL_TXMIX ; 
 scalar_t__ b43_debug (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_suspend (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lock (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_unlock (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_put_attenuation_into_ranges (struct b43_wldev*,int*,int*) ; 
 int /*<<< orphan*/  b43_radio_lock (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_unlock (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_set_txpower_g (struct b43_wldev*,TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void b43_gphy_op_adjust_txpower(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	int rfatt, bbatt;
	u8 tx_control;

	b43_mac_suspend(dev);

	/* Calculate the new attenuation values. */
	bbatt = gphy->bbatt.att;
	bbatt += gphy->bbatt_delta;
	rfatt = gphy->rfatt.att;
	rfatt += gphy->rfatt_delta;

	b43_put_attenuation_into_ranges(dev, &bbatt, &rfatt);
	tx_control = gphy->tx_control;
	if ((phy->radio_ver == 0x2050) && (phy->radio_rev == 2)) {
		if (rfatt <= 1) {
			if (tx_control == 0) {
				tx_control =
				    B43_TXCTL_PA2DB |
				    B43_TXCTL_TXMIX;
				rfatt += 2;
				bbatt += 2;
			} else if (dev->dev->bus_sprom->
				   boardflags_lo &
				   B43_BFL_PACTRL) {
				bbatt += 4 * (rfatt - 2);
				rfatt = 2;
			}
		} else if (rfatt > 4 && tx_control) {
			tx_control = 0;
			if (bbatt < 3) {
				rfatt -= 3;
				bbatt += 2;
			} else {
				rfatt -= 2;
				bbatt -= 2;
			}
		}
	}
	/* Save the control values */
	gphy->tx_control = tx_control;
	b43_put_attenuation_into_ranges(dev, &bbatt, &rfatt);
	gphy->rfatt.att = rfatt;
	gphy->bbatt.att = bbatt;

	if (b43_debug(dev, B43_DBG_XMITPOWER))
		b43dbg(dev->wl, "Adjusting TX power\n");

	/* Adjust the hardware */
	b43_phy_lock(dev);
	b43_radio_lock(dev);
	b43_set_txpower_g(dev, &gphy->bbatt, &gphy->rfatt,
			  gphy->tx_control);
	b43_radio_unlock(dev);
	b43_phy_unlock(dev);

	b43_mac_enable(dev);
}