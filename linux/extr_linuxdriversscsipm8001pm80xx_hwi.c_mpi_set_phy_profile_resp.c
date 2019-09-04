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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct set_phy_profile_resp {int /*<<< orphan*/  status; int /*<<< orphan*/  ppc_phyid; } ;
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ SAS_PHY_ANALOG_SETTINGS_PAGE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,scalar_t__) ; 

__attribute__((used)) static int mpi_set_phy_profile_resp(struct pm8001_hba_info *pm8001_ha,
			void *piomb)
{
	u8 page_code;
	struct set_phy_profile_resp *pPayload =
		(struct set_phy_profile_resp *)(piomb + 4);
	u32 ppc_phyid = le32_to_cpu(pPayload->ppc_phyid);
	u32 status = le32_to_cpu(pPayload->status);

	page_code = (u8)((ppc_phyid & 0xFF00) >> 8);
	if (status) {
		/* status is FAILED */
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("PhyProfile command failed  with status "
			"0x%08X \n", status));
		return -1;
	} else {
		if (page_code != SAS_PHY_ANALOG_SETTINGS_PAGE) {
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("Invalid page code 0x%X\n",
					page_code));
			return -1;
		}
	}
	return 0;
}