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
struct pci_dev {int revision; } ;
struct hisi_sas_phy {int dummy; } ;
struct hisi_hba {struct device* dev; struct pci_dev* pci_dev; struct hisi_sas_phy* phy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CHL_INT2 ; 
 int /*<<< orphan*/  CHL_INT2_MSK ; 
 int CHL_INT2_RX_INVLD_DW_OFF ; 
 int CHL_INT2_SL_IDAF_TOUT_CONF_OFF ; 
 int CHL_INT2_STP_LINK_TIMEOUT_OFF ; 
 int /*<<< orphan*/  HILINK_ERR_DFX ; 
 int /*<<< orphan*/  HISI_PHYE_LINK_RESET ; 
 int /*<<< orphan*/  STP_LINK_TIMEOUT_STATE ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  hisi_sas_notify_phy_event (struct hisi_sas_phy*,int /*<<< orphan*/ ) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int hisi_sas_read32_poll_timeout_atomic (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void handle_chl_int2_v3_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	u32 irq_msk = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT2_MSK);
	u32 irq_value = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT2);
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct pci_dev *pci_dev = hisi_hba->pci_dev;
	struct device *dev = hisi_hba->dev;

	irq_value &= ~irq_msk;
	if (!irq_value)
		return;

	if (irq_value & BIT(CHL_INT2_SL_IDAF_TOUT_CONF_OFF)) {
		dev_warn(dev, "phy%d identify timeout\n", phy_no);
		hisi_sas_notify_phy_event(phy, HISI_PHYE_LINK_RESET);
	}

	if (irq_value & BIT(CHL_INT2_STP_LINK_TIMEOUT_OFF)) {
		u32 reg_value = hisi_sas_phy_read32(hisi_hba, phy_no,
				STP_LINK_TIMEOUT_STATE);

		dev_warn(dev, "phy%d stp link timeout (0x%x)\n",
			 phy_no, reg_value);
		if (reg_value & BIT(4))
			hisi_sas_notify_phy_event(phy, HISI_PHYE_LINK_RESET);
	}

	if ((irq_value & BIT(CHL_INT2_RX_INVLD_DW_OFF)) &&
	    (pci_dev->revision == 0x20)) {
		u32 reg_value;
		int rc;

		rc = hisi_sas_read32_poll_timeout_atomic(
				HILINK_ERR_DFX, reg_value,
				!((reg_value >> 8) & BIT(phy_no)),
				1000, 10000);
		if (rc)
			hisi_sas_notify_phy_event(phy, HISI_PHYE_LINK_RESET);
	}

	hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT2, irq_value);
}