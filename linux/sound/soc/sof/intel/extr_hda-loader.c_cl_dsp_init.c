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
typedef  int /*<<< orphan*/  u32 ;
struct sof_intel_hda_dev {struct sof_intel_dsp_desc* desc; } ;
struct sof_intel_dsp_desc {int cores_mask; int ssp_count; int ipc_req_mask; unsigned int ipc_ack_mask; int rom_init_timeout; int /*<<< orphan*/  ipc_ack; int /*<<< orphan*/  ipc_req; scalar_t__ ssp_base_offset; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct TYPE_2__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int HDA_DSP_CORE_MASK (int /*<<< orphan*/ ) ; 
 int HDA_DSP_INIT_TIMEOUT_US ; 
 int HDA_DSP_IPC_PURGE_FW ; 
 int /*<<< orphan*/  HDA_DSP_REG_POLL_INTERVAL_US ; 
 unsigned int HDA_DSP_ROM_INIT ; 
 unsigned int HDA_DSP_ROM_STS_MASK ; 
 int /*<<< orphan*/  HDA_DSP_SRAM_REG_ROM_STATUS ; 
 int SOF_DBG_MBOX ; 
 int SOF_DBG_PCI ; 
 int SOF_DBG_REGS ; 
 int SSP_DEV_MEM_SIZE ; 
 int /*<<< orphan*/  SSP_SET_SLAVE ; 
 scalar_t__ SSP_SSC1_OFFSET ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hda_dsp_core_power_down (struct snd_sof_dev*,int) ; 
 int hda_dsp_core_power_up (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  hda_dsp_core_reset_power_down (struct snd_sof_dev*,int) ; 
 int hda_dsp_core_run (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  hda_dsp_dump (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  hda_dsp_ipc_int_enable (struct snd_sof_dev*) ; 
 int snd_sof_dsp_read_poll_timeout (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_unlocked (struct snd_sof_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_write (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cl_dsp_init(struct snd_sof_dev *sdev, const void *fwdata,
		       u32 fwsize, int stream_tag)
{
	struct sof_intel_hda_dev *hda = sdev->pdata->hw_pdata;
	const struct sof_intel_dsp_desc *chip = hda->desc;
	unsigned int status;
	int ret;
	int i;

	/* step 1: power up corex */
	ret = hda_dsp_core_power_up(sdev, chip->cores_mask);
	if (ret < 0) {
		dev_err(sdev->dev, "error: dsp core 0/1 power up failed\n");
		goto err;
	}

	/* DSP is powered up, set all SSPs to slave mode */
	for (i = 0; i < chip->ssp_count; i++) {
		snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
						 chip->ssp_base_offset
						 + i * SSP_DEV_MEM_SIZE
						 + SSP_SSC1_OFFSET,
						 SSP_SET_SLAVE,
						 SSP_SET_SLAVE);
	}

	/* step 2: purge FW request */
	snd_sof_dsp_write(sdev, HDA_DSP_BAR, chip->ipc_req,
			  chip->ipc_req_mask | (HDA_DSP_IPC_PURGE_FW |
			  ((stream_tag - 1) << 9)));

	/* step 3: unset core 0 reset state & unstall/run core 0 */
	ret = hda_dsp_core_run(sdev, HDA_DSP_CORE_MASK(0));
	if (ret < 0) {
		dev_err(sdev->dev, "error: dsp core start failed %d\n", ret);
		ret = -EIO;
		goto err;
	}

	/* step 4: wait for IPC DONE bit from ROM */
	ret = snd_sof_dsp_read_poll_timeout(sdev, HDA_DSP_BAR,
					    chip->ipc_ack, status,
					    ((status & chip->ipc_ack_mask)
						    == chip->ipc_ack_mask),
					    HDA_DSP_REG_POLL_INTERVAL_US,
					    HDA_DSP_INIT_TIMEOUT_US);

	if (ret < 0) {
		dev_err(sdev->dev, "error: waiting for HIPCIE done\n");
		goto err;
	}

	/* step 5: power down corex */
	ret = hda_dsp_core_power_down(sdev,
				  chip->cores_mask & ~(HDA_DSP_CORE_MASK(0)));
	if (ret < 0) {
		dev_err(sdev->dev, "error: dsp core x power down failed\n");
		goto err;
	}

	/* step 6: enable IPC interrupts */
	hda_dsp_ipc_int_enable(sdev);

	/* step 7: wait for ROM init */
	ret = snd_sof_dsp_read_poll_timeout(sdev, HDA_DSP_BAR,
					HDA_DSP_SRAM_REG_ROM_STATUS, status,
					((status & HDA_DSP_ROM_STS_MASK)
						== HDA_DSP_ROM_INIT),
					HDA_DSP_REG_POLL_INTERVAL_US,
					chip->rom_init_timeout *
					USEC_PER_MSEC);
	if (!ret)
		return 0;

err:
	hda_dsp_dump(sdev, SOF_DBG_REGS | SOF_DBG_PCI | SOF_DBG_MBOX);
	hda_dsp_core_reset_power_down(sdev, chip->cores_mask);

	return ret;
}