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
struct b43_phy {struct b43_phy_ht* ht; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_ht {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct b43_phy_ht*) ; 

__attribute__((used)) static void b43_phy_ht_op_free(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_ht *phy_ht = phy->ht;

	kfree(phy_ht);
	phy->ht = NULL;
}