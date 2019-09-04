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
struct hisi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CONTEXT ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_sata_phy_v2_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	u32 context;

	context = hisi_sas_read32(hisi_hba, PHY_CONTEXT);
	if (context & (1 << phy_no))
		return true;

	return false;
}