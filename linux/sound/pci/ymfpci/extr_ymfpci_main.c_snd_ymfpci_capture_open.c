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
typedef  size_t u32 ;
struct snd_ymfpci_pcm {size_t capture_bank_number; struct snd_pcm_substream* substream; scalar_t__ type; struct snd_ymfpci* chip; } ;
struct snd_ymfpci {struct snd_pcm_substream** capture_substream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  private_free; struct snd_ymfpci_pcm* private_data; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ CAPTURE_REC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_TIME ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct snd_ymfpci_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_rule_noresample (struct snd_pcm_runtime*,int) ; 
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ymfpci_capture ; 
 int /*<<< orphan*/  snd_ymfpci_hw_start (struct snd_ymfpci*) ; 
 int /*<<< orphan*/  snd_ymfpci_pcm_free_substream ; 

__attribute__((used)) static int snd_ymfpci_capture_open(struct snd_pcm_substream *substream,
				   u32 capture_bank_number)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ymfpci_pcm *ypcm;
	int err;

	runtime->hw = snd_ymfpci_capture;
	/* FIXME? True value is 256/48 = 5.33333 ms */
	err = snd_pcm_hw_constraint_minmax(runtime,
					   SNDRV_PCM_HW_PARAM_PERIOD_TIME,
					   5334, UINT_MAX);
	if (err < 0)
		return err;
	err = snd_pcm_hw_rule_noresample(runtime, 48000);
	if (err < 0)
		return err;

	ypcm = kzalloc(sizeof(*ypcm), GFP_KERNEL);
	if (ypcm == NULL)
		return -ENOMEM;
	ypcm->chip = chip;
	ypcm->type = capture_bank_number + CAPTURE_REC;
	ypcm->substream = substream;	
	ypcm->capture_bank_number = capture_bank_number;
	chip->capture_substream[capture_bank_number] = substream;
	runtime->private_data = ypcm;
	runtime->private_free = snd_ymfpci_pcm_free_substream;
	snd_ymfpci_hw_start(chip);
	return 0;
}