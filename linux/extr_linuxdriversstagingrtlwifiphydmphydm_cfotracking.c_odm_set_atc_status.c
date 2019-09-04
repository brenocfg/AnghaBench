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
struct cfo_tracking {int is_atc_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_ATC ; 
 int /*<<< orphan*/  ODM_BIT (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int /*<<< orphan*/  PHYDM_CFOTRACK ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void odm_set_atc_status(void *dm_void, bool atc_status)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct cfo_tracking *cfo_track =
		(struct cfo_tracking *)phydm_get_structure(dm, PHYDM_CFOTRACK);

	if (cfo_track->is_atc_status == atc_status)
		return;

	odm_set_bb_reg(dm, ODM_REG(BB_ATC, dm), ODM_BIT(BB_ATC, dm),
		       atc_status);
	cfo_track->is_atc_status = atc_status;
}