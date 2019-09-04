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
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_deaf_mode (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_nphy_deaf_mode (struct brcms_phy*,int) ; 

void wlc_phy_set_deaf(struct brcms_phy_pub *ppi, bool user_flag)
{
	struct brcms_phy *pi;
	pi = (struct brcms_phy *) ppi;

	if (ISLCNPHY(pi))
		wlc_lcnphy_deaf_mode(pi, true);
	else if (ISNPHY(pi))
		wlc_nphy_deaf_mode(pi, true);
}