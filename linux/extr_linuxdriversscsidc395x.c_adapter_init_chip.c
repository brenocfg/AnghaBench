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
struct NvRamType {int channel_cfg; int delay_time; } ;
struct AdapterCtlBlk {int config; struct NvRamType eeprom; scalar_t__ last_reset; } ;

/* Variables and functions */
 int DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int DMARESETMODULE ; 
 int /*<<< orphan*/  DO_RSTMODULE ; 
 int DO_RSTSCSI ; 
 int HCC_AUTOTERM ; 
 int HCC_PARITY ; 
 int HCC_SCSI_RESET ; 
 int HCC_WIDE_CARD ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int NAC_POWERON_SCSI_RESET ; 
 int /*<<< orphan*/  TRM_S1040_DMA_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_DMA_INTEN ; 
 int /*<<< orphan*/  TRM_S1040_GEN_STATUS ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_INTEN ; 
 int WIDESCSI ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void adapter_init_chip(struct AdapterCtlBlk *acb)
{
        struct NvRamType *eeprom = &acb->eeprom;
        
        /* Mask all the interrupt */
	DC395x_write8(acb, TRM_S1040_DMA_INTEN, 0x00);
	DC395x_write8(acb, TRM_S1040_SCSI_INTEN, 0x00);

	/* Reset SCSI module */
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_RSTMODULE);

	/* Reset PCI/DMA module */
	DC395x_write8(acb, TRM_S1040_DMA_CONTROL, DMARESETMODULE);
	udelay(20);

	/* program configuration 0 */
	acb->config = HCC_AUTOTERM | HCC_PARITY;
	if (DC395x_read8(acb, TRM_S1040_GEN_STATUS) & WIDESCSI)
		acb->config |= HCC_WIDE_CARD;

	if (eeprom->channel_cfg & NAC_POWERON_SCSI_RESET)
		acb->config |= HCC_SCSI_RESET;

	if (acb->config & HCC_SCSI_RESET) {
		dprintkl(KERN_INFO, "Performing initial SCSI bus reset\n");
		DC395x_write8(acb, TRM_S1040_SCSI_CONTROL, DO_RSTSCSI);

		/*while (!( DC395x_read8(acb, TRM_S1040_SCSI_INTSTATUS) & INT_SCSIRESET )); */
		/*spin_unlock_irq (&io_request_lock); */
		udelay(500);

		acb->last_reset =
		    jiffies + HZ / 2 +
		    HZ * acb->eeprom.delay_time;

		/*spin_lock_irq (&io_request_lock); */
	}
}