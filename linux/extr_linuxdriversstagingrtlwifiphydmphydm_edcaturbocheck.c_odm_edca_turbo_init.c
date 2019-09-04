#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int is_current_turbo_edca; int is_cur_rdl_state; } ;
struct phy_dm_struct {TYPE_1__ dm_edca_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_EDCA_TURBO ; 
 int /*<<< orphan*/  ODM_EDCA_BE_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_BK_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_VI_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_VO_PARAM ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_read_4byte (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

void odm_edca_turbo_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	dm->dm_edca_table.is_current_turbo_edca = false;
	dm->dm_edca_table.is_cur_rdl_state = false;

	ODM_RT_TRACE(dm, ODM_COMP_EDCA_TURBO, "Orginial VO PARAM: 0x%x\n",
		     odm_read_4byte(dm, ODM_EDCA_VO_PARAM));
	ODM_RT_TRACE(dm, ODM_COMP_EDCA_TURBO, "Orginial VI PARAM: 0x%x\n",
		     odm_read_4byte(dm, ODM_EDCA_VI_PARAM));
	ODM_RT_TRACE(dm, ODM_COMP_EDCA_TURBO, "Orginial BE PARAM: 0x%x\n",
		     odm_read_4byte(dm, ODM_EDCA_BE_PARAM));
	ODM_RT_TRACE(dm, ODM_COMP_EDCA_TURBO, "Orginial BK PARAM: 0x%x\n",
		     odm_read_4byte(dm, ODM_EDCA_BK_PARAM));

}