#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ code; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  HDA_DSP_SRAM_REG_ROM_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* hda_dsp_rom_msg ; 
 scalar_t__ snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hda_dsp_get_status(struct snd_sof_dev *sdev)
{
	u32 status;
	int i;

	status = snd_sof_dsp_read(sdev, HDA_DSP_BAR,
				  HDA_DSP_SRAM_REG_ROM_STATUS);

	for (i = 0; i < ARRAY_SIZE(hda_dsp_rom_msg); i++) {
		if (status == hda_dsp_rom_msg[i].code) {
			dev_err(sdev->dev, "%s - code %8.8x\n",
				hda_dsp_rom_msg[i].msg, status);
			return;
		}
	}

	/* not for us, must be generic sof message */
	dev_dbg(sdev->dev, "unknown ROM status value %8.8x\n", status);
}