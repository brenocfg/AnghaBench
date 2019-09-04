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
struct b43_phy {struct b43_phy_lp* lp; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_lp {int /*<<< orphan*/  antenna; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_ANTENNA_DEFAULT ; 
 int /*<<< orphan*/  memset (struct b43_phy_lp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_lpphy_op_prepare_structs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_lp *lpphy = phy->lp;

	memset(lpphy, 0, sizeof(*lpphy));
	lpphy->antenna = B43_ANTENNA_DEFAULT;

	//TODO
}