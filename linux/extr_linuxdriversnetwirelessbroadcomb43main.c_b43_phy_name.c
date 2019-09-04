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
typedef  int u8 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
#define  B43_PHYTYPE_A 138 
#define  B43_PHYTYPE_AC 137 
#define  B43_PHYTYPE_B 136 
#define  B43_PHYTYPE_G 135 
#define  B43_PHYTYPE_HT 134 
#define  B43_PHYTYPE_LCN 133 
#define  B43_PHYTYPE_LCN40 132 
#define  B43_PHYTYPE_LCNXN 131 
#define  B43_PHYTYPE_LP 130 
#define  B43_PHYTYPE_N 129 
#define  B43_PHYTYPE_SSLPN 128 

__attribute__((used)) static char *b43_phy_name(struct b43_wldev *dev, u8 phy_type)
{
	switch (phy_type) {
	case B43_PHYTYPE_A:
		return "A";
	case B43_PHYTYPE_B:
		return "B";
	case B43_PHYTYPE_G:
		return "G";
	case B43_PHYTYPE_N:
		return "N";
	case B43_PHYTYPE_LP:
		return "LP";
	case B43_PHYTYPE_SSLPN:
		return "SSLPN";
	case B43_PHYTYPE_HT:
		return "HT";
	case B43_PHYTYPE_LCN:
		return "LCN";
	case B43_PHYTYPE_LCNXN:
		return "LCNXN";
	case B43_PHYTYPE_LCN40:
		return "LCN40";
	case B43_PHYTYPE_AC:
		return "AC";
	}
	return "UNKNOWN";
}