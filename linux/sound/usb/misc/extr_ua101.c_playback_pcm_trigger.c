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
struct ua101 {int /*<<< orphan*/  states; } ;
struct snd_pcm_substream {struct ua101* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALSA_PLAYBACK_RUNNING ; 
 int EINVAL ; 
 int EIO ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  USB_PLAYBACK_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int playback_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct ua101 *ua = substream->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (!test_bit(USB_PLAYBACK_RUNNING, &ua->states))
			return -EIO;
		set_bit(ALSA_PLAYBACK_RUNNING, &ua->states);
		return 0;
	case SNDRV_PCM_TRIGGER_STOP:
		clear_bit(ALSA_PLAYBACK_RUNNING, &ua->states);
		return 0;
	default:
		return -EINVAL;
	}
}