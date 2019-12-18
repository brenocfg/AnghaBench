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
typedef  int u64 ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct fw_device {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  generation; int /*<<< orphan*/  node_id; int /*<<< orphan*/  card; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BEBOB_ADDR_REG_REQ ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INFO_OFFSET_SW_DATE ; 
 int /*<<< orphan*/  MAUDIO_BOOTLOADER_CUE1 ; 
 int /*<<< orphan*/  MAUDIO_BOOTLOADER_CUE2 ; 
 int /*<<< orphan*/  MAUDIO_BOOTLOADER_CUE3 ; 
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct fw_device* fw_parent_device (struct fw_unit*) ; 
 int fw_run_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int snd_bebob_read_block (struct fw_unit*,int /*<<< orphan*/ ,int*,int) ; 

int snd_bebob_maudio_load_firmware(struct fw_unit *unit)
{
	struct fw_device *device = fw_parent_device(unit);
	int err, rcode;
	u64 date;
	__le32 *cues;

	/* check date of software used to build */
	err = snd_bebob_read_block(unit, INFO_OFFSET_SW_DATE,
				   &date, sizeof(u64));
	if (err < 0)
		return err;
	/*
	 * firmware version 5058 or later has date later than "20070401", but
	 * 'date' is not null-terminated.
	 */
	if (date < 0x3230303730343031LL) {
		dev_err(&unit->device,
			"Use firmware version 5058 or later\n");
		return -ENXIO;
	}

	cues = kmalloc_array(3, sizeof(*cues), GFP_KERNEL);
	if (!cues)
		return -ENOMEM;

	cues[0] = cpu_to_le32(MAUDIO_BOOTLOADER_CUE1);
	cues[1] = cpu_to_le32(MAUDIO_BOOTLOADER_CUE2);
	cues[2] = cpu_to_le32(MAUDIO_BOOTLOADER_CUE3);

	rcode = fw_run_transaction(device->card, TCODE_WRITE_BLOCK_REQUEST,
				   device->node_id, device->generation,
				   device->max_speed, BEBOB_ADDR_REG_REQ,
				   cues, 3 * sizeof(*cues));
	kfree(cues);
	if (rcode != RCODE_COMPLETE) {
		dev_err(&unit->device,
			"Failed to send a cue to load firmware\n");
		err = -EIO;
	}

	return err;
}