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
struct TYPE_4__ {unsigned int ctl; } ;
struct snd_cs46xx {unsigned int play_ctl; TYPE_2__ capt; TYPE_1__* card; int /*<<< orphan*/ * modules; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA1_CCTL ; 
 int /*<<< orphan*/  BA1_CVOL ; 
 int /*<<< orphan*/  BA1_PCTL ; 
 int /*<<< orphan*/  BA1_PVOL ; 
 int CS46XX_DSP_MODULES ; 
 int EIO ; 
 int cs46xx_dsp_load_module (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 scalar_t__ cs46xx_dsp_scb_and_task_init (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  cs46xx_enable_stream_irqs (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int load_firmware (struct snd_cs46xx*,...) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/ * module_names ; 
 int snd_cs46xx_download_image (struct snd_cs46xx*) ; 
 unsigned int snd_cs46xx_peek (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_cs46xx_proc_start (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  snd_cs46xx_reset (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  snd_cs46xx_set_capture_sample_rate (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  snd_cs46xx_set_play_sample_rate (struct snd_cs46xx*,int) ; 

int snd_cs46xx_start_dsp(struct snd_cs46xx *chip)
{	
	unsigned int tmp;
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	int i;
#endif
	int err;

	/*
	 *  Reset the processor.
	 */
	snd_cs46xx_reset(chip);
	/*
	 *  Download the image to the processor.
	 */
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	for (i = 0; i < CS46XX_DSP_MODULES; i++) {
		err = load_firmware(chip, &chip->modules[i], module_names[i]);
		if (err < 0) {
			dev_err(chip->card->dev, "firmware load error [%s]\n",
				   module_names[i]);
			return err;
		}
		err = cs46xx_dsp_load_module(chip, chip->modules[i]);
		if (err < 0) {
			dev_err(chip->card->dev, "image download error [%s]\n",
				   module_names[i]);
			return err;
		}
	}

	if (cs46xx_dsp_scb_and_task_init(chip) < 0)
		return -EIO;
#else
	err = load_firmware(chip);
	if (err < 0)
		return err;

	/* old image */
	err = snd_cs46xx_download_image(chip);
	if (err < 0) {
		dev_err(chip->card->dev, "image download error\n");
		return err;
	}

	/*
         *  Stop playback DMA.
	 */
	tmp = snd_cs46xx_peek(chip, BA1_PCTL);
	chip->play_ctl = tmp & 0xffff0000;
	snd_cs46xx_poke(chip, BA1_PCTL, tmp & 0x0000ffff);
#endif

	/*
         *  Stop capture DMA.
	 */
	tmp = snd_cs46xx_peek(chip, BA1_CCTL);
	chip->capt.ctl = tmp & 0x0000ffff;
	snd_cs46xx_poke(chip, BA1_CCTL, tmp & 0xffff0000);

	mdelay(5);

	snd_cs46xx_set_play_sample_rate(chip, 8000);
	snd_cs46xx_set_capture_sample_rate(chip, 8000);

	snd_cs46xx_proc_start(chip);

	cs46xx_enable_stream_irqs(chip);
	
#ifndef CONFIG_SND_CS46XX_NEW_DSP
	/* set the attenuation to 0dB */ 
	snd_cs46xx_poke(chip, BA1_PVOL, 0x80008000);
	snd_cs46xx_poke(chip, BA1_CVOL, 0x80008000);
#endif

	return 0;
}