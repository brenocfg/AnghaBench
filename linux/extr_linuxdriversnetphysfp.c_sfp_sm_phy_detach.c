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
struct sfp {int /*<<< orphan*/ * mod_phy; int /*<<< orphan*/  sfp_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_device_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_device_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfp_remove_phy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfp_sm_phy_detach(struct sfp *sfp)
{
	phy_stop(sfp->mod_phy);
	sfp_remove_phy(sfp->sfp_bus);
	phy_device_remove(sfp->mod_phy);
	phy_device_free(sfp->mod_phy);
	sfp->mod_phy = NULL;
}