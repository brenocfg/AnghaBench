#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  sense_uproc_interrupt_reg32; int /*<<< orphan*/  clr_interrupt_reg; int /*<<< orphan*/  clr_uproc_interrupt_reg32; int /*<<< orphan*/  set_uproc_interrupt_reg32; } ;
struct ipr_ioa_cfg {TYPE_2__ regs; int /*<<< orphan*/  ioa_mailbox; TYPE_1__* pdev; scalar_t__ sis64; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int IPR_LDUMP_MAX_LONG_ACK_DELAY_IN_USEC ; 
 int IPR_LDUMP_MAX_SHORT_ACK_DELAY_IN_USEC ; 
 int volatile IPR_PCII_IO_DEBUG_ACKNOWLEDGE ; 
 int volatile IPR_UPROCI_IO_DEBUG_ALERT ; 
 int volatile IPR_UPROCI_RESET_ALERT ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ipr_get_sis64_dump_data_section (struct ipr_ioa_cfg*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ipr_wait_iodbg_ack (struct ipr_ioa_cfg*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int volatile,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipr_get_ldump_data_section(struct ipr_ioa_cfg *ioa_cfg,
				      u32 start_addr,
				      __be32 *dest, u32 length_in_words)
{
	volatile u32 temp_pcii_reg;
	int i, delay = 0;

	if (ioa_cfg->sis64)
		return ipr_get_sis64_dump_data_section(ioa_cfg, start_addr,
						       dest, length_in_words);

	/* Write IOA interrupt reg starting LDUMP state  */
	writel((IPR_UPROCI_RESET_ALERT | IPR_UPROCI_IO_DEBUG_ALERT),
	       ioa_cfg->regs.set_uproc_interrupt_reg32);

	/* Wait for IO debug acknowledge */
	if (ipr_wait_iodbg_ack(ioa_cfg,
			       IPR_LDUMP_MAX_LONG_ACK_DELAY_IN_USEC)) {
		dev_err(&ioa_cfg->pdev->dev,
			"IOA dump long data transfer timeout\n");
		return -EIO;
	}

	/* Signal LDUMP interlocked - clear IO debug ack */
	writel(IPR_PCII_IO_DEBUG_ACKNOWLEDGE,
	       ioa_cfg->regs.clr_interrupt_reg);

	/* Write Mailbox with starting address */
	writel(start_addr, ioa_cfg->ioa_mailbox);

	/* Signal address valid - clear IOA Reset alert */
	writel(IPR_UPROCI_RESET_ALERT,
	       ioa_cfg->regs.clr_uproc_interrupt_reg32);

	for (i = 0; i < length_in_words; i++) {
		/* Wait for IO debug acknowledge */
		if (ipr_wait_iodbg_ack(ioa_cfg,
				       IPR_LDUMP_MAX_SHORT_ACK_DELAY_IN_USEC)) {
			dev_err(&ioa_cfg->pdev->dev,
				"IOA dump short data transfer timeout\n");
			return -EIO;
		}

		/* Read data from mailbox and increment destination pointer */
		*dest = cpu_to_be32(readl(ioa_cfg->ioa_mailbox));
		dest++;

		/* For all but the last word of data, signal data received */
		if (i < (length_in_words - 1)) {
			/* Signal dump data received - Clear IO debug Ack */
			writel(IPR_PCII_IO_DEBUG_ACKNOWLEDGE,
			       ioa_cfg->regs.clr_interrupt_reg);
		}
	}

	/* Signal end of block transfer. Set reset alert then clear IO debug ack */
	writel(IPR_UPROCI_RESET_ALERT,
	       ioa_cfg->regs.set_uproc_interrupt_reg32);

	writel(IPR_UPROCI_IO_DEBUG_ALERT,
	       ioa_cfg->regs.clr_uproc_interrupt_reg32);

	/* Signal dump data received - Clear IO debug Ack */
	writel(IPR_PCII_IO_DEBUG_ACKNOWLEDGE,
	       ioa_cfg->regs.clr_interrupt_reg);

	/* Wait for IOA to signal LDUMP exit - IOA reset alert will be cleared */
	while (delay < IPR_LDUMP_MAX_SHORT_ACK_DELAY_IN_USEC) {
		temp_pcii_reg =
		    readl(ioa_cfg->regs.sense_uproc_interrupt_reg32);

		if (!(temp_pcii_reg & IPR_UPROCI_RESET_ALERT))
			return 0;

		udelay(10);
		delay += 10;
	}

	return 0;
}