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
struct expander_device {struct ex_phy* ex_phy; } ;
struct ex_phy {int /*<<< orphan*/  linkrate; } ;
struct domain_device {struct expander_device ex_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_FUNC_DISABLE ; 
 int /*<<< orphan*/  SAS_PHY_DISABLED ; 
 int /*<<< orphan*/  sas_smp_phy_control (struct domain_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sas_ex_disable_phy(struct domain_device *dev, int phy_id)
{
	struct expander_device *ex = &dev->ex_dev;
	struct ex_phy *phy = &ex->ex_phy[phy_id];

	sas_smp_phy_control(dev, phy_id, PHY_FUNC_DISABLE, NULL);
	phy->linkrate = SAS_PHY_DISABLED;
}