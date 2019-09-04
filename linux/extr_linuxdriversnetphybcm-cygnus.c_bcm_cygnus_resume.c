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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int bcm_cygnus_config_init (struct phy_device*) ; 
 int genphy_config_aneg (struct phy_device*) ; 
 int /*<<< orphan*/  genphy_resume (struct phy_device*) ; 

__attribute__((used)) static int bcm_cygnus_resume(struct phy_device *phydev)
{
	int rc;

	genphy_resume(phydev);

	/* Re-initialize the PHY to apply AFE work-arounds and
	 * configurations when coming out of suspend.
	 */
	rc = bcm_cygnus_config_init(phydev);
	if (rc)
		return rc;

	/* restart auto negotiation with the new settings */
	return genphy_config_aneg(phydev);
}