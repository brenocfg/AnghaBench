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
typedef  void* u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct NvRamType {int sub_class; int reserved; int cksum; int /*<<< orphan*/  delay_time; scalar_t__ target; void** device_id; void** vendor_id; void** sub_sys_id; void** sub_vendor_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 size_t CFG_RESET_DELAY ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int PCI_DEVICE_ID_TEKRAM_TRMS1040 ; 
 int PCI_VENDOR_ID_TEKRAM ; 
 TYPE_1__* cfg_data ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  eeprom_index_to_delay (struct NvRamType*) ; 
 int /*<<< orphan*/  eeprom_override (struct NvRamType*) ; 
 int /*<<< orphan*/  fix_settings () ; 
 int /*<<< orphan*/  set_safe_settings () ; 
 int /*<<< orphan*/  trms1040_read_all (struct NvRamType*,unsigned long) ; 
 int /*<<< orphan*/  trms1040_write_all (struct NvRamType*,unsigned long) ; 

__attribute__((used)) static void check_eeprom(struct NvRamType *eeprom, unsigned long io_port)
{
	u16 *w_eeprom = (u16 *)eeprom;
	u16 w_addr;
	u16 cksum;
	u32 d_addr;
	u32 *d_eeprom;

	trms1040_read_all(eeprom, io_port);	/* read eeprom */

	cksum = 0;
	for (w_addr = 0, w_eeprom = (u16 *)eeprom; w_addr < 64;
	     w_addr++, w_eeprom++)
		cksum += *w_eeprom;
	if (cksum != 0x1234) {
		/*
		 * Checksum is wrong.
		 * Load a set of defaults into the eeprom buffer
		 */
		dprintkl(KERN_WARNING,
			"EEProm checksum error: using default values and options.\n");
		eeprom->sub_vendor_id[0] = (u8)PCI_VENDOR_ID_TEKRAM;
		eeprom->sub_vendor_id[1] = (u8)(PCI_VENDOR_ID_TEKRAM >> 8);
		eeprom->sub_sys_id[0] = (u8)PCI_DEVICE_ID_TEKRAM_TRMS1040;
		eeprom->sub_sys_id[1] =
		    (u8)(PCI_DEVICE_ID_TEKRAM_TRMS1040 >> 8);
		eeprom->sub_class = 0x00;
		eeprom->vendor_id[0] = (u8)PCI_VENDOR_ID_TEKRAM;
		eeprom->vendor_id[1] = (u8)(PCI_VENDOR_ID_TEKRAM >> 8);
		eeprom->device_id[0] = (u8)PCI_DEVICE_ID_TEKRAM_TRMS1040;
		eeprom->device_id[1] =
		    (u8)(PCI_DEVICE_ID_TEKRAM_TRMS1040 >> 8);
		eeprom->reserved = 0x00;

		for (d_addr = 0, d_eeprom = (u32 *)eeprom->target;
		     d_addr < 16; d_addr++, d_eeprom++)
			*d_eeprom = 0x00000077;	/* cfg3,cfg2,period,cfg0 */

		*d_eeprom++ = 0x04000F07;	/* max_tag,delay_time,channel_cfg,scsi_id */
		*d_eeprom++ = 0x00000015;	/* reserved1,boot_lun,boot_target,reserved0 */
		for (d_addr = 0; d_addr < 12; d_addr++, d_eeprom++)
			*d_eeprom = 0x00;

		/* Now load defaults (maybe set by boot/module params) */
		set_safe_settings();
		fix_settings();
		eeprom_override(eeprom);

		eeprom->cksum = 0x00;
		for (w_addr = 0, cksum = 0, w_eeprom = (u16 *)eeprom;
		     w_addr < 63; w_addr++, w_eeprom++)
			cksum += *w_eeprom;

		*w_eeprom = 0x1234 - cksum;
		trms1040_write_all(eeprom, io_port);
		eeprom->delay_time = cfg_data[CFG_RESET_DELAY].value;
	} else {
		set_safe_settings();
		eeprom_index_to_delay(eeprom);
		eeprom_override(eeprom);
	}
}