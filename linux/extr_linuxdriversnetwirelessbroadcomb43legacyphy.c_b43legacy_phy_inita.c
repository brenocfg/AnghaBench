#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct b43legacy_wldev {TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_4__ {int boardflags_lo; } ;
struct TYPE_5__ {TYPE_1__ sprom; } ;

/* Variables and functions */
 int B43legacy_BFL_PACTRL ; 
 int /*<<< orphan*/  b43legacy_phy_setupg (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  might_sleep () ; 

__attribute__((used)) static void b43legacy_phy_inita(struct b43legacy_wldev *dev)
{

	might_sleep();

	b43legacy_phy_setupg(dev);
	if (dev->dev->bus->sprom.boardflags_lo & B43legacy_BFL_PACTRL)
		b43legacy_phy_write(dev, 0x046E, 0x03CF);
}