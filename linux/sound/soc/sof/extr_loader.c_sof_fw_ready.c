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
typedef  int /*<<< orphan*/  u32 ;
struct sof_ipc_fw_ready {int dummy; } ;
struct snd_sof_dev {int /*<<< orphan*/  first_boot; int /*<<< orphan*/  dev; struct sof_ipc_fw_ready fw_ready; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SOF_FW_BLK_TYPE_SRAM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_sof_dsp_get_bar_index (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int snd_sof_dsp_get_mailbox_offset (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_fw_parse_ext_data (struct snd_sof_dev*,int,int) ; 
 int snd_sof_ipc_valid (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  sof_block_read (struct snd_sof_dev*,int,int,struct sof_ipc_fw_ready*,int) ; 
 int /*<<< orphan*/  sof_get_windows (struct snd_sof_dev*) ; 

int sof_fw_ready(struct snd_sof_dev *sdev, u32 msg_id)
{
	struct sof_ipc_fw_ready *fw_ready = &sdev->fw_ready;
	int offset;
	int bar;
	int ret;

	/* mailbox must be on 4k boundary */
	offset = snd_sof_dsp_get_mailbox_offset(sdev);
	if (offset < 0) {
		dev_err(sdev->dev, "error: have no mailbox offset\n");
		return offset;
	}

	bar = snd_sof_dsp_get_bar_index(sdev, SOF_FW_BLK_TYPE_SRAM);
	if (bar < 0) {
		dev_err(sdev->dev, "error: have no bar mapping\n");
		return -EINVAL;
	}

	dev_dbg(sdev->dev, "ipc: DSP is ready 0x%8.8x offset 0x%x\n",
		msg_id, offset);

	/* no need to re-check version/ABI for subsequent boots */
	if (!sdev->first_boot)
		return 0;

	/* copy data from the DSP FW ready offset */
	sof_block_read(sdev, bar, offset, fw_ready, sizeof(*fw_ready));

	/* make sure ABI version is compatible */
	ret = snd_sof_ipc_valid(sdev);
	if (ret < 0)
		return ret;

	/* now check for extended data */
	snd_sof_fw_parse_ext_data(sdev, bar, offset +
				  sizeof(struct sof_ipc_fw_ready));

	sof_get_windows(sdev);

	return 0;
}