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
struct snd_tscm {int /*<<< orphan*/  unit; } ;
struct snd_info_entry {struct snd_tscm* private_data; } ;
struct snd_info_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 scalar_t__ TSCM_ADDR_BASE ; 
 scalar_t__ TSCM_OFFSET_FIRMWARE_ARM ; 
 scalar_t__ TSCM_OFFSET_FIRMWARE_FPGA ; 
 scalar_t__ TSCM_OFFSET_FIRMWARE_HW ; 
 scalar_t__ TSCM_OFFSET_FIRMWARE_REGISTER ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void proc_read_firmware(struct snd_info_entry *entry,
			       struct snd_info_buffer *buffer)
{
	struct snd_tscm *tscm = entry->private_data;
	__be32 data;
	unsigned int reg, fpga, arm, hw;
	int err;

	err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
			TSCM_ADDR_BASE + TSCM_OFFSET_FIRMWARE_REGISTER,
			&data, sizeof(data), 0);
	if (err < 0)
		return;
	reg = be32_to_cpu(data);

	err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
			TSCM_ADDR_BASE + TSCM_OFFSET_FIRMWARE_FPGA,
			&data, sizeof(data), 0);
	if (err < 0)
		return;
	fpga = be32_to_cpu(data);

	err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
			TSCM_ADDR_BASE + TSCM_OFFSET_FIRMWARE_ARM,
			&data, sizeof(data), 0);
	if (err < 0)
		return;
	arm = be32_to_cpu(data);

	err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
			TSCM_ADDR_BASE + TSCM_OFFSET_FIRMWARE_HW,
			&data, sizeof(data), 0);
	if (err < 0)
		return;
	hw = be32_to_cpu(data);

	snd_iprintf(buffer, "Register: %d (0x%08x)\n", reg & 0xffff, reg);
	snd_iprintf(buffer, "FPGA:     %d (0x%08x)\n", fpga & 0xffff, fpga);
	snd_iprintf(buffer, "ARM:      %d (0x%08x)\n", arm & 0xffff, arm);
	snd_iprintf(buffer, "Hardware: %d (0x%08x)\n", hw >> 16, hw);
}