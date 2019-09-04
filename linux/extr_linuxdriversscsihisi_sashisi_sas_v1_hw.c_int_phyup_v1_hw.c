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
typedef  int u32 ;
struct sas_identify_frame {scalar_t__ dev_type; int /*<<< orphan*/  sas_addr; } ;
struct TYPE_2__ {scalar_t__ device_type; int /*<<< orphan*/  target_port_protocols; } ;
struct asd_sas_phy {int id; int linkrate; int /*<<< orphan*/  attached_sas_addr; int /*<<< orphan*/  oob_mode; scalar_t__ frame_rcvd; } ;
struct hisi_sas_phy {int port_id; int phy_type; int phy_attached; int frame_rcvd_size; int /*<<< orphan*/  lock; scalar_t__ reset_completion; scalar_t__ in_reset; TYPE_1__ identify; struct asd_sas_phy sas_phy; struct hisi_hba* hisi_hba; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CHL_INT0 ; 
 scalar_t__ CHL_INT0_MSK ; 
 int CHL_INT0_PHYCTRL_NOTRDY_MSK ; 
 scalar_t__ CHL_INT2 ; 
 int CHL_INT2_SL_PHY_ENA_MSK ; 
 int /*<<< orphan*/  HISI_PHYE_PHY_UP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PHY_CONN_RATE ; 
 int /*<<< orphan*/  PHY_CONTEXT ; 
 int /*<<< orphan*/  PHY_PORT_NUM_MA ; 
 int PORT_TYPE_SAS ; 
 int PORT_TYPE_SATA ; 
 scalar_t__ RX_IDAF_DWORD0 ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 scalar_t__ SAS_END_DEVICE ; 
 int /*<<< orphan*/  SAS_OOB_MODE ; 
 scalar_t__ SAS_PHY_UNUSED ; 
 int /*<<< orphan*/  SAS_PROTOCOL_SMP ; 
 int /*<<< orphan*/  SAS_PROTOCOL_SSP ; 
 int __swab32 (int) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  hisi_sas_notify_phy_event (struct hisi_sas_phy*,int /*<<< orphan*/ ) ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,scalar_t__) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,scalar_t__,int) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t int_phyup_v1_hw(int irq_no, void *p)
{
	struct hisi_sas_phy *phy = p;
	struct hisi_hba *hisi_hba = phy->hisi_hba;
	struct device *dev = hisi_hba->dev;
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	int i, phy_no = sas_phy->id;
	u32 irq_value, context, port_id, link_rate;
	u32 *frame_rcvd = (u32 *)sas_phy->frame_rcvd;
	struct sas_identify_frame *id = (struct sas_identify_frame *)frame_rcvd;
	irqreturn_t res = IRQ_HANDLED;
	unsigned long flags;

	irq_value = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT2);
	if (!(irq_value & CHL_INT2_SL_PHY_ENA_MSK)) {
		dev_dbg(dev, "phyup: irq_value = %x not set enable bit\n",
			irq_value);
		res = IRQ_NONE;
		goto end;
	}

	context = hisi_sas_read32(hisi_hba, PHY_CONTEXT);
	if (context & 1 << phy_no) {
		dev_err(dev, "phyup: phy%d SATA attached equipment\n",
			phy_no);
		goto end;
	}

	port_id = (hisi_sas_read32(hisi_hba, PHY_PORT_NUM_MA) >> (4 * phy_no))
		  & 0xf;
	if (port_id == 0xf) {
		dev_err(dev, "phyup: phy%d invalid portid\n", phy_no);
		res = IRQ_NONE;
		goto end;
	}

	for (i = 0; i < 6; i++) {
		u32 idaf = hisi_sas_phy_read32(hisi_hba, phy_no,
					RX_IDAF_DWORD0 + (i * 4));
		frame_rcvd[i] = __swab32(idaf);
	}

	/* Get the linkrate */
	link_rate = hisi_sas_read32(hisi_hba, PHY_CONN_RATE);
	link_rate = (link_rate >> (phy_no * 4)) & 0xf;
	sas_phy->linkrate = link_rate;
	sas_phy->oob_mode = SAS_OOB_MODE;
	memcpy(sas_phy->attached_sas_addr,
		&id->sas_addr, SAS_ADDR_SIZE);
	dev_info(dev, "phyup: phy%d link_rate=%d\n",
		 phy_no, link_rate);
	phy->port_id = port_id;
	phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	phy->phy_type |= PORT_TYPE_SAS;
	phy->phy_attached = 1;
	phy->identify.device_type = id->dev_type;
	phy->frame_rcvd_size =	sizeof(struct sas_identify_frame);
	if (phy->identify.device_type == SAS_END_DEVICE)
		phy->identify.target_port_protocols =
			SAS_PROTOCOL_SSP;
	else if (phy->identify.device_type != SAS_PHY_UNUSED)
		phy->identify.target_port_protocols =
			SAS_PROTOCOL_SMP;
	hisi_sas_notify_phy_event(phy, HISI_PHYE_PHY_UP);

	spin_lock_irqsave(&phy->lock, flags);
	if (phy->reset_completion) {
		phy->in_reset = 0;
		complete(phy->reset_completion);
	}
	spin_unlock_irqrestore(&phy->lock, flags);

end:
	hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT2,
			     CHL_INT2_SL_PHY_ENA_MSK);

	if (irq_value & CHL_INT2_SL_PHY_ENA_MSK) {
		u32 chl_int0 = hisi_sas_phy_read32(hisi_hba, phy_no, CHL_INT0);

		chl_int0 &= ~CHL_INT0_PHYCTRL_NOTRDY_MSK;
		hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT0, chl_int0);
		hisi_sas_phy_write32(hisi_hba, phy_no, CHL_INT0_MSK, 0x3ce3ee);
	}

	return res;
}