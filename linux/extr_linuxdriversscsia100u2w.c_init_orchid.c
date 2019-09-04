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
typedef  int u8 ;
typedef  int u16 ;
struct orc_host {int* target_flag; scalar_t__ base; int /*<<< orphan*/  flags; int /*<<< orphan*/ * max_tags; int /*<<< orphan*/  max_targets; int /*<<< orphan*/  BIOScfg; int /*<<< orphan*/  scsi_id; } ;
struct TYPE_2__ {int revision; int SCSI0Config; int /*<<< orphan*/  Target00Config; int /*<<< orphan*/  BIOSConfig1; int /*<<< orphan*/  scsi_id; } ;

/* Variables and functions */
 int DEVRST ; 
 int /*<<< orphan*/  HCF_SCSI_RESET ; 
 int HDO ; 
 int /*<<< orphan*/  MAX_TARGETS ; 
 int NCC_BUSRESET ; 
 scalar_t__ ORC_GIMSK ; 
 scalar_t__ ORC_HCTRL ; 
 scalar_t__ ORC_HSTUS ; 
 int /*<<< orphan*/  ORC_MAXTAGS ; 
 int RREADY ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  init_alloc_map (struct orc_host*) ; 
 TYPE_1__* nvramp ; 
 int /*<<< orphan*/  orc_load_firmware (struct orc_host*) ; 
 int orc_read_fwrev (struct orc_host*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  read_eeprom (struct orc_host*) ; 
 int /*<<< orphan*/  setup_SCBs (struct orc_host*) ; 
 scalar_t__ wait_chip_ready (struct orc_host*) ; 
 scalar_t__ wait_firmware_ready (struct orc_host*) ; 

__attribute__((used)) static int init_orchid(struct orc_host * host)
{
	u8 *ptr;
	u16 revision;
	u8 i;

	init_alloc_map(host);
	outb(0xFF, host->base + ORC_GIMSK);	/* Disable all interrupts */

	if (inb(host->base + ORC_HSTUS) & RREADY) {	/* Orchid is ready */
		revision = orc_read_fwrev(host);
		if (revision == 0xFFFF) {
			outb(DEVRST, host->base + ORC_HCTRL);	/* Reset Host Adapter   */
			if (wait_chip_ready(host) == 0)
				return -1;
			orc_load_firmware(host);	/* Download FW                  */
			setup_SCBs(host);	/* Setup SCB base and SCB Size registers */
			outb(0x00, host->base + ORC_HCTRL);	/* clear HOSTSTOP       */
			if (wait_firmware_ready(host) == 0)
				return -1;
			/* Wait for firmware ready     */
		} else {
			setup_SCBs(host);	/* Setup SCB base and SCB Size registers */
		}
	} else {		/* Orchid is not Ready          */
		outb(DEVRST, host->base + ORC_HCTRL);	/* Reset Host Adapter   */
		if (wait_chip_ready(host) == 0)
			return -1;
		orc_load_firmware(host);	/* Download FW                  */
		setup_SCBs(host);	/* Setup SCB base and SCB Size registers */
		outb(HDO, host->base + ORC_HCTRL);	/* Do Hardware Reset &  */

		/*     clear HOSTSTOP  */
		if (wait_firmware_ready(host) == 0)		/* Wait for firmware ready      */
			return -1;
	}

	/* Load an EEProm copy into RAM */
	/* Assumes single threaded at this point */
	read_eeprom(host);

	if (nvramp->revision != 1)
		return -1;

	host->scsi_id = nvramp->scsi_id;
	host->BIOScfg = nvramp->BIOSConfig1;
	host->max_targets = MAX_TARGETS;
	ptr = (u8 *) & (nvramp->Target00Config);
	for (i = 0; i < 16; ptr++, i++) {
		host->target_flag[i] = *ptr;
		host->max_tags[i] = ORC_MAXTAGS;
	}

	if (nvramp->SCSI0Config & NCC_BUSRESET)
		host->flags |= HCF_SCSI_RESET;
	outb(0xFB, host->base + ORC_GIMSK);	/* enable RP FIFO interrupt     */
	return 0;
}