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
typedef  scalar_t__ u32 ;
struct hisi_hba {int n_phy; int /*<<< orphan*/  ctrl_reset_sts_reg; scalar_t__ ctrl; scalar_t__ ctrl_clock_ena_reg; scalar_t__ ctrl_reset_reg; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  AXI_CFG ; 
 int /*<<< orphan*/  DLVRY_QUEUE_ENABLE ; 
 int /*<<< orphan*/  DMA_RX_STATUS ; 
 scalar_t__ DMA_RX_STATUS_BUSY_MSK ; 
 int /*<<< orphan*/  DMA_TX_STATUS ; 
 scalar_t__ DMA_TX_STATUS_BUSY_MSK ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  PHY_CFG ; 
 scalar_t__ PHY_CTRL_RESET_MSK ; 
 int /*<<< orphan*/  acpi_evaluate_object (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  regmap_write (scalar_t__,scalar_t__,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int reset_hw_v2_hw(struct hisi_hba *hisi_hba)
{
	int i, reset_val;
	u32 val;
	unsigned long end_time;
	struct device *dev = hisi_hba->dev;

	/* The mask needs to be set depending on the number of phys */
	if (hisi_hba->n_phy == 9)
		reset_val = 0x1fffff;
	else
		reset_val = 0x7ffff;

	hisi_sas_write32(hisi_hba, DLVRY_QUEUE_ENABLE, 0);

	/* Disable all of the PHYs */
	for (i = 0; i < hisi_hba->n_phy; i++) {
		u32 phy_cfg = hisi_sas_phy_read32(hisi_hba, i, PHY_CFG);

		phy_cfg &= ~PHY_CTRL_RESET_MSK;
		hisi_sas_phy_write32(hisi_hba, i, PHY_CFG, phy_cfg);
	}
	udelay(50);

	/* Ensure DMA tx & rx idle */
	for (i = 0; i < hisi_hba->n_phy; i++) {
		u32 dma_tx_status, dma_rx_status;

		end_time = jiffies + msecs_to_jiffies(1000);

		while (1) {
			dma_tx_status = hisi_sas_phy_read32(hisi_hba, i,
							    DMA_TX_STATUS);
			dma_rx_status = hisi_sas_phy_read32(hisi_hba, i,
							    DMA_RX_STATUS);

			if (!(dma_tx_status & DMA_TX_STATUS_BUSY_MSK) &&
				!(dma_rx_status & DMA_RX_STATUS_BUSY_MSK))
				break;

			msleep(20);
			if (time_after(jiffies, end_time))
				return -EIO;
		}
	}

	/* Ensure axi bus idle */
	end_time = jiffies + msecs_to_jiffies(1000);
	while (1) {
		u32 axi_status =
			hisi_sas_read32(hisi_hba, AXI_CFG);

		if (axi_status == 0)
			break;

		msleep(20);
		if (time_after(jiffies, end_time))
			return -EIO;
	}

	if (ACPI_HANDLE(dev)) {
		acpi_status s;

		s = acpi_evaluate_object(ACPI_HANDLE(dev), "_RST", NULL, NULL);
		if (ACPI_FAILURE(s)) {
			dev_err(dev, "Reset failed\n");
			return -EIO;
		}
	} else if (hisi_hba->ctrl) {
		/* reset and disable clock*/
		regmap_write(hisi_hba->ctrl, hisi_hba->ctrl_reset_reg,
				reset_val);
		regmap_write(hisi_hba->ctrl, hisi_hba->ctrl_clock_ena_reg + 4,
				reset_val);
		msleep(1);
		regmap_read(hisi_hba->ctrl, hisi_hba->ctrl_reset_sts_reg, &val);
		if (reset_val != (val & reset_val)) {
			dev_err(dev, "SAS reset fail.\n");
			return -EIO;
		}

		/* De-reset and enable clock*/
		regmap_write(hisi_hba->ctrl, hisi_hba->ctrl_reset_reg + 4,
				reset_val);
		regmap_write(hisi_hba->ctrl, hisi_hba->ctrl_clock_ena_reg,
				reset_val);
		msleep(1);
		regmap_read(hisi_hba->ctrl, hisi_hba->ctrl_reset_sts_reg,
				&val);
		if (val & reset_val) {
			dev_err(dev, "SAS de-reset fail.\n");
			return -EIO;
		}
	} else {
		dev_err(dev, "no reset method\n");
		return -EINVAL;
	}

	return 0;
}