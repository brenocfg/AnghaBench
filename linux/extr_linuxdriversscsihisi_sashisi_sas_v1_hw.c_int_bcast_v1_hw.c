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
struct sas_ha_struct {int /*<<< orphan*/  (* notify_port_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;} ;
struct asd_sas_phy {int id; } ;
struct hisi_sas_phy {struct asd_sas_phy sas_phy; struct hisi_hba* hisi_hba; } ;
struct hisi_hba {int /*<<< orphan*/  flags; struct device* dev; struct sas_ha_struct sha; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHL_INT2 ; 
 int CHL_INT2_SL_RX_BC_ACK_MSK ; 
 int /*<<< orphan*/  HISI_SAS_RESET_BIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PORTE_BROADCAST_RCVD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t int_bcast_v1_hw(int irq, void *p)
{
	struct hisi_sas_phy *phy = p;
	struct hisi_hba *hisi_hba = phy->hisi_hba;
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	struct sas_ha_struct *sha = &hisi_hba->sha;
	struct device *dev = hisi_hba->dev;
	int phy_no = sas_phy->id;
	u32 irq_value;
	irqreturn_t res = IRQ_HANDLED;

	irq_value = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT2);

	if (!(irq_value & CHL_INT2_SL_RX_BC_ACK_MSK)) {
		dev_err(dev, "bcast: irq_value = %x not set enable bit",
			irq_value);
		res = IRQ_NONE;
		goto end;
	}

	if (!test_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags))
		sha->notify_port_event(sas_phy, PORTE_BROADCAST_RCVD);

end:
	hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT2,
			     CHL_INT2_SL_RX_BC_ACK_MSK);

	return res;
}