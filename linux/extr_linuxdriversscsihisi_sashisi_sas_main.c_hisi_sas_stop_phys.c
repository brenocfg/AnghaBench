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
struct hisi_hba {int n_phy; TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* phy_disable ) (struct hisi_hba*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hisi_hba*,int) ; 

void hisi_sas_stop_phys(struct hisi_hba *hisi_hba)
{
	int phy_no;

	for (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++)
		hisi_hba->hw->phy_disable(hisi_hba, phy_no);
}