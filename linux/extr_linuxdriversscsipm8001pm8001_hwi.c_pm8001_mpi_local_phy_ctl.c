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
typedef  scalar_t__ u32 ;
struct pm8001_hba_info {TYPE_1__* phy; } ;
struct local_phy_ctl_resp {int /*<<< orphan*/  tag; int /*<<< orphan*/  phyop_phyid; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int reset_success; int /*<<< orphan*/ * enable_completion; } ;

/* Variables and functions */
 scalar_t__ ID_BITS ; 
 scalar_t__ OP_BITS ; 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,scalar_t__) ; 

int pm8001_mpi_local_phy_ctl(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	u32 tag;
	struct local_phy_ctl_resp *pPayload =
		(struct local_phy_ctl_resp *)(piomb + 4);
	u32 status = le32_to_cpu(pPayload->status);
	u32 phy_id = le32_to_cpu(pPayload->phyop_phyid) & ID_BITS;
	u32 phy_op = le32_to_cpu(pPayload->phyop_phyid) & OP_BITS;
	tag = le32_to_cpu(pPayload->tag);
	if (status != 0) {
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("%x phy execute %x phy op failed!\n",
			phy_id, phy_op));
	} else {
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("%x phy execute %x phy op success!\n",
			phy_id, phy_op));
		pm8001_ha->phy[phy_id].reset_success = true;
	}
	if (pm8001_ha->phy[phy_id].enable_completion) {
		complete(pm8001_ha->phy[phy_id].enable_completion);
		pm8001_ha->phy[phy_id].enable_completion = NULL;
	}
	pm8001_tag_free(pm8001_ha, tag);
	return 0;
}