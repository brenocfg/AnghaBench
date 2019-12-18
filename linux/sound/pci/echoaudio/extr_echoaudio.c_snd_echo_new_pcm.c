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
struct snd_pcm {int /*<<< orphan*/  name; struct echoaudio* private_data; } ;
struct echoaudio {int /*<<< orphan*/  pci; TYPE_1__* card; struct snd_pcm* digital_pcm; struct snd_pcm* analog_pcm; } ;
struct TYPE_2__ {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  analog_capture_ops ; 
 int /*<<< orphan*/  analog_playback_ops ; 
 int /*<<< orphan*/  digital_capture_ops ; 
 int /*<<< orphan*/  digital_playback_ops ; 
 int /*<<< orphan*/  num_analog_busses_in (struct echoaudio*) ; 
 int /*<<< orphan*/  num_analog_busses_out (struct echoaudio*) ; 
 int /*<<< orphan*/  num_digital_busses_in (struct echoaudio*) ; 
 int /*<<< orphan*/  num_digital_busses_out (struct echoaudio*) ; 
 int /*<<< orphan*/  num_pipes_out (struct echoaudio*) ; 
 int /*<<< orphan*/  snd_dma_pci_data (int /*<<< orphan*/ ) ; 
 int snd_echo_preallocate_pages (struct snd_pcm*,int /*<<< orphan*/ ) ; 
 int snd_pcm_new (TYPE_1__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_echo_new_pcm(struct echoaudio *chip)
{
	struct snd_pcm *pcm;
	int err;

#ifdef ECHOCARD_HAS_VMIXER
	/* This card has a Vmixer, that is there is no direct mapping from PCM
	streams to physical outputs. The user can mix the streams as he wishes
	via control interface and it's possible to send any stream to any
	output, thus it makes no sense to keep analog and digital outputs
	separated */

	/* PCM#0 Virtual outputs and analog inputs */
	if ((err = snd_pcm_new(chip->card, "PCM", 0, num_pipes_out(chip),
				num_analog_busses_in(chip), &pcm)) < 0)
		return err;
	pcm->private_data = chip;
	chip->analog_pcm = pcm;
	strcpy(pcm->name, chip->card->shortname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &analog_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &analog_capture_ops);
	if ((err = snd_echo_preallocate_pages(pcm, snd_dma_pci_data(chip->pci))) < 0)
		return err;

#ifdef ECHOCARD_HAS_DIGITAL_IO
	/* PCM#1 Digital inputs, no outputs */
	if ((err = snd_pcm_new(chip->card, "Digital PCM", 1, 0,
			       num_digital_busses_in(chip), &pcm)) < 0)
		return err;
	pcm->private_data = chip;
	chip->digital_pcm = pcm;
	strcpy(pcm->name, chip->card->shortname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &digital_capture_ops);
	if ((err = snd_echo_preallocate_pages(pcm, snd_dma_pci_data(chip->pci))) < 0)
		return err;
#endif /* ECHOCARD_HAS_DIGITAL_IO */

#else /* ECHOCARD_HAS_VMIXER */

	/* The card can manage substreams formed by analog and digital channels
	at the same time, but I prefer to keep analog and digital channels
	separated, because that mixed thing is confusing and useless. So we
	register two PCM devices: */

	/* PCM#0 Analog i/o */
	if ((err = snd_pcm_new(chip->card, "Analog PCM", 0,
			       num_analog_busses_out(chip),
			       num_analog_busses_in(chip), &pcm)) < 0)
		return err;
	pcm->private_data = chip;
	chip->analog_pcm = pcm;
	strcpy(pcm->name, chip->card->shortname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &analog_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &analog_capture_ops);
	if ((err = snd_echo_preallocate_pages(pcm, snd_dma_pci_data(chip->pci))) < 0)
		return err;

#ifdef ECHOCARD_HAS_DIGITAL_IO
	/* PCM#1 Digital i/o */
	if ((err = snd_pcm_new(chip->card, "Digital PCM", 1,
			       num_digital_busses_out(chip),
			       num_digital_busses_in(chip), &pcm)) < 0)
		return err;
	pcm->private_data = chip;
	chip->digital_pcm = pcm;
	strcpy(pcm->name, chip->card->shortname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &digital_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &digital_capture_ops);
	if ((err = snd_echo_preallocate_pages(pcm, snd_dma_pci_data(chip->pci))) < 0)
		return err;
#endif /* ECHOCARD_HAS_DIGITAL_IO */

#endif /* ECHOCARD_HAS_VMIXER */

	return 0;
}