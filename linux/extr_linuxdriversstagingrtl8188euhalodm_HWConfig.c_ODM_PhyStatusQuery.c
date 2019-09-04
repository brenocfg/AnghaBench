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
typedef  int /*<<< orphan*/  u8 ;
struct odm_phy_status_info {int dummy; } ;
struct odm_per_pkt_info {int dummy; } ;
struct odm_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_PhyStatusQuery_92CSeries (struct odm_dm_struct*,struct odm_phy_status_info*,int /*<<< orphan*/ *,struct odm_per_pkt_info*) ; 

void ODM_PhyStatusQuery(struct odm_dm_struct *dm_odm,
			struct odm_phy_status_info *pPhyInfo,
			u8 *pPhyStatus, struct odm_per_pkt_info *pPktinfo)
{
	ODM_PhyStatusQuery_92CSeries(dm_odm, pPhyInfo, pPhyStatus, pPktinfo);
}