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
struct TYPE_2__ {struct b43_phy_g* g; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_rfatt {int dummy; } ;
struct b43_phy_g {int /*<<< orphan*/  bbatt; int /*<<< orphan*/  rfatt; } ;
struct b43_lo_calib {int /*<<< orphan*/  ctl; } ;
typedef  int /*<<< orphan*/  rf ;

/* Variables and functions */
 struct b43_lo_calib* b43_get_calib_lo_settings (struct b43_wldev*,int /*<<< orphan*/ *,struct b43_rfatt*) ; 
 int /*<<< orphan*/  b43_lo_fixup_rfatt (struct b43_rfatt*) ; 
 int /*<<< orphan*/  b43_lo_write (struct b43_wldev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct b43_rfatt*,int /*<<< orphan*/ *,int) ; 

void b43_lo_g_adjust(struct b43_wldev *dev)
{
	struct b43_phy_g *gphy = dev->phy.g;
	struct b43_lo_calib *cal;
	struct b43_rfatt rf;

	memcpy(&rf, &gphy->rfatt, sizeof(rf));
	b43_lo_fixup_rfatt(&rf);

	cal = b43_get_calib_lo_settings(dev, &gphy->bbatt, &rf);
	if (!cal)
		return;
	b43_lo_write(dev, &cal->ctl);
}