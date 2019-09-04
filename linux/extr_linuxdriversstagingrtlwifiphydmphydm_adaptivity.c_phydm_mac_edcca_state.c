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
struct phy_dm_struct {int dummy; } ;
typedef  enum phydm_mac_edcca_type { ____Placeholder_phydm_mac_edcca_type } phydm_mac_edcca_type ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PHYDM_COMP_ADAPTIVITY ; 
 int /*<<< orphan*/  REG_TX_PTCL_CTRL ; 
 int /*<<< orphan*/  odm_set_mac_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int phydm_ignore_edcca ; 

void phydm_mac_edcca_state(void *dm_void, enum phydm_mac_edcca_type state)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (state == phydm_ignore_edcca) {
		/*ignore EDCCA	reg520[15]=1*/
		odm_set_mac_reg(dm, REG_TX_PTCL_CTRL, BIT(15), 1);
	} else { /*don't set MAC ignore EDCCA signal*/
		/*don't ignore EDCCA	 reg520[15]=0*/
		odm_set_mac_reg(dm, REG_TX_PTCL_CTRL, BIT(15), 0);
	}
	ODM_RT_TRACE(dm, PHYDM_COMP_ADAPTIVITY, "EDCCA enable state = %d\n",
		     state);
}