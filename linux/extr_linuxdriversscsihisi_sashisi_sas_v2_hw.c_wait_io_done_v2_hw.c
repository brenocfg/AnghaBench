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
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TX_DFX0 ; 
 int /*<<< orphan*/  LINK_DFX2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool wait_io_done_v2_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	int i, max_loop = 1000;
	struct device *dev = hisi_hba->dev;
	u32 status, tx_dfx0;

	for (i = 0; i < max_loop; i++) {
		status = hisi_sas_phy_read32(hisi_hba, phy_no, LINK_DFX2);
		status = (status & 0x3fc0) >> 6;

		if (status != 0x1)
			return true;

		tx_dfx0 = hisi_sas_phy_read32(hisi_hba, phy_no, DMA_TX_DFX0);
		if ((tx_dfx0 & 0x1ff) == 0x2)
			return true;
		udelay(10);
	}
	dev_err(dev, "IO not done phy%d, port264:0x%x port200:0x%x\n",
			phy_no, status, tx_dfx0);
	return false;
}