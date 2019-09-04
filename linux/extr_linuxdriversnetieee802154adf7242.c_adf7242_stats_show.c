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
typedef  int u8 ;
struct seq_file {int /*<<< orphan*/  private; } ;
struct adf7242_local {int /*<<< orphan*/  rssi; } ;

/* Variables and functions */
 int IRQ_ADDRESS_VALID ; 
 int IRQ_CCA_COMPLETE ; 
 int IRQ_CSMA_CA ; 
 int IRQ_FRAME_VALID ; 
 int IRQ_RX_PKT_RCVD ; 
 int IRQ_SFD_RX ; 
 int IRQ_SFD_TX ; 
 int IRQ_TX_PKT_SENT ; 
 int RC_STATUS_IDLE ; 
 int RC_STATUS_MEAS ; 
 int RC_STATUS_PHY_RDY ; 
 int RC_STATUS_RX ; 
 int RC_STATUS_TX ; 
 int /*<<< orphan*/  REG_IRQ1_SRC1 ; 
 int STAT_CCA_RESULT ; 
 int STAT_IRQ_STATUS ; 
 int STAT_RC_READY ; 
 int STAT_SPI_READY ; 
 int /*<<< orphan*/  adf7242_read_reg (struct adf7242_local*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  adf7242_status (struct adf7242_local*,int*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 struct adf7242_local* spi_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adf7242_stats_show(struct seq_file *file, void *offset)
{
	struct adf7242_local *lp = spi_get_drvdata(file->private);
	u8 stat, irq1;

	adf7242_status(lp, &stat);
	adf7242_read_reg(lp, REG_IRQ1_SRC1, &irq1);

	seq_printf(file, "IRQ1 = %X:\n%s%s%s%s%s%s%s%s\n", irq1,
		   irq1 & IRQ_CCA_COMPLETE ? "IRQ_CCA_COMPLETE\n" : "",
		   irq1 & IRQ_SFD_RX ? "IRQ_SFD_RX\n" : "",
		   irq1 & IRQ_SFD_TX ? "IRQ_SFD_TX\n" : "",
		   irq1 & IRQ_RX_PKT_RCVD ? "IRQ_RX_PKT_RCVD\n" : "",
		   irq1 & IRQ_TX_PKT_SENT ? "IRQ_TX_PKT_SENT\n" : "",
		   irq1 & IRQ_CSMA_CA ? "IRQ_CSMA_CA\n" : "",
		   irq1 & IRQ_FRAME_VALID ? "IRQ_FRAME_VALID\n" : "",
		   irq1 & IRQ_ADDRESS_VALID ? "IRQ_ADDRESS_VALID\n" : "");

	seq_printf(file, "STATUS = %X:\n%s\n%s\n%s\n%s\n%s%s%s%s%s\n", stat,
		   stat & STAT_SPI_READY ? "SPI_READY" : "SPI_BUSY",
		   stat & STAT_IRQ_STATUS ? "IRQ_PENDING" : "IRQ_CLEAR",
		   stat & STAT_RC_READY ? "RC_READY" : "RC_BUSY",
		   stat & STAT_CCA_RESULT ? "CHAN_IDLE" : "CHAN_BUSY",
		   (stat & 0xf) == RC_STATUS_IDLE ? "RC_STATUS_IDLE" : "",
		   (stat & 0xf) == RC_STATUS_MEAS ? "RC_STATUS_MEAS" : "",
		   (stat & 0xf) == RC_STATUS_PHY_RDY ? "RC_STATUS_PHY_RDY" : "",
		   (stat & 0xf) == RC_STATUS_RX ? "RC_STATUS_RX" : "",
		   (stat & 0xf) == RC_STATUS_TX ? "RC_STATUS_TX" : "");

	seq_printf(file, "RSSI = %d\n", lp->rssi);

	return 0;
}