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
struct niu {int flags; void* mac_xcvr; } ;

/* Variables and functions */
 int EINVAL ; 
 void* MAC_XCVR_MII ; 
 void* MAC_XCVR_PCS ; 
 void* MAC_XCVR_XPCS ; 
 int NIU_FLAGS_10G ; 
 int NIU_FLAGS_FIBER ; 
 int NIU_FLAGS_XCVR_SERDES ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int niu_phy_type_prop_decode(struct niu *np, const char *phy_prop)
{
	if (!strcmp(phy_prop, "mif")) {
		/* 1G copper, MII */
		np->flags &= ~(NIU_FLAGS_FIBER |
			       NIU_FLAGS_10G);
		np->mac_xcvr = MAC_XCVR_MII;
	} else if (!strcmp(phy_prop, "xgf")) {
		/* 10G fiber, XPCS */
		np->flags |= (NIU_FLAGS_10G |
			      NIU_FLAGS_FIBER);
		np->mac_xcvr = MAC_XCVR_XPCS;
	} else if (!strcmp(phy_prop, "pcs")) {
		/* 1G fiber, PCS */
		np->flags &= ~NIU_FLAGS_10G;
		np->flags |= NIU_FLAGS_FIBER;
		np->mac_xcvr = MAC_XCVR_PCS;
	} else if (!strcmp(phy_prop, "xgc")) {
		/* 10G copper, XPCS */
		np->flags |= NIU_FLAGS_10G;
		np->flags &= ~NIU_FLAGS_FIBER;
		np->mac_xcvr = MAC_XCVR_XPCS;
	} else if (!strcmp(phy_prop, "xgsd") || !strcmp(phy_prop, "gsd")) {
		/* 10G Serdes or 1G Serdes, default to 10G */
		np->flags |= NIU_FLAGS_10G;
		np->flags &= ~NIU_FLAGS_FIBER;
		np->flags |= NIU_FLAGS_XCVR_SERDES;
		np->mac_xcvr = MAC_XCVR_XPCS;
	} else {
		return -EINVAL;
	}
	return 0;
}