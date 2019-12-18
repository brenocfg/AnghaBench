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
struct snd_pcm_substream {struct isight* private_data; } ;
struct isight {int /*<<< orphan*/  pcm_running; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int isight_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct isight *isight = substream->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		WRITE_ONCE(isight->pcm_running, true);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		WRITE_ONCE(isight->pcm_running, false);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}