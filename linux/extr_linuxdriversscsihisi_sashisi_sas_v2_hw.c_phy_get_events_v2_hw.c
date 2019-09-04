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
typedef  int u32 ;
struct sas_phy {int loss_of_dword_sync_count; int phy_reset_problem_count; int invalid_dword_count; int running_disparity_error_count; } ;
struct asd_sas_phy {struct sas_phy* phy; } ;
struct hisi_sas_phy {struct asd_sas_phy sas_phy; } ;
struct hisi_hba {struct hisi_sas_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ERR_CNT4_REG ; 
 int /*<<< orphan*/  SAS_ERR_CNT6_REG ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phy_get_events_v2_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	struct sas_phy *sphy = sas_phy->phy;
	u32 err4_reg_val, err6_reg_val;

	/* loss dword syn, phy reset problem */
	err4_reg_val = hisi_sas_phy_read32(hisi_hba, phy_no, SAS_ERR_CNT4_REG);

	/* disparity err, invalid dword */
	err6_reg_val = hisi_sas_phy_read32(hisi_hba, phy_no, SAS_ERR_CNT6_REG);

	sphy->loss_of_dword_sync_count += (err4_reg_val >> 16) & 0xFFFF;
	sphy->phy_reset_problem_count += err4_reg_val & 0xFFFF;
	sphy->invalid_dword_count += (err6_reg_val & 0xFF0000) >> 16;
	sphy->running_disparity_error_count += err6_reg_val & 0xFF;
}