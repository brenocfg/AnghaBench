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
struct b43legacy_phy {struct b43legacy_lopair* _lo_pairs; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;
struct b43legacy_lopair {scalar_t__ used; } ;

/* Variables and functions */
 int B43legacy_LO_COUNT ; 

void b43legacy_phy_lo_mark_all_unused(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	struct b43legacy_lopair *pair;
	int i;

	for (i = 0; i < B43legacy_LO_COUNT; i++) {
		pair = phy->_lo_pairs + i;
		pair->used = 0;
	}
}