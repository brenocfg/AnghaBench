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
struct snd_pcm_substream {struct snd_pcm_substream* next; } ;
struct snd_pcm {TYPE_1__* streams; int /*<<< orphan*/  list; int /*<<< orphan*/  device; int /*<<< orphan*/  card; } ;
struct snd_device {struct snd_pcm* device_data; } ;
struct TYPE_2__ {struct snd_pcm_substream* substream; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int SNDRV_DEVICE_TYPE_PCM_CAPTURE ; 
 int SNDRV_DEVICE_TYPE_PCM_PLAYBACK ; 
#define  SNDRV_PCM_STREAM_CAPTURE 129 
#define  SNDRV_PCM_STREAM_PLAYBACK 128 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_register ; 
 int /*<<< orphan*/  pcm_call_notify (struct snd_pcm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mutex ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_pcm_add (struct snd_pcm*) ; 
 int /*<<< orphan*/ * snd_pcm_f_ops ; 
 int /*<<< orphan*/  snd_pcm_timer_init (struct snd_pcm_substream*) ; 
 int snd_register_device (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct snd_pcm*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_dev_register(struct snd_device *device)
{
	int cidx, err;
	struct snd_pcm_substream *substream;
	struct snd_pcm *pcm;

	if (snd_BUG_ON(!device || !device->device_data))
		return -ENXIO;
	pcm = device->device_data;

	mutex_lock(&register_mutex);
	err = snd_pcm_add(pcm);
	if (err)
		goto unlock;
	for (cidx = 0; cidx < 2; cidx++) {
		int devtype = -1;
		if (pcm->streams[cidx].substream == NULL)
			continue;
		switch (cidx) {
		case SNDRV_PCM_STREAM_PLAYBACK:
			devtype = SNDRV_DEVICE_TYPE_PCM_PLAYBACK;
			break;
		case SNDRV_PCM_STREAM_CAPTURE:
			devtype = SNDRV_DEVICE_TYPE_PCM_CAPTURE;
			break;
		}
		/* register pcm */
		err = snd_register_device(devtype, pcm->card, pcm->device,
					  &snd_pcm_f_ops[cidx], pcm,
					  &pcm->streams[cidx].dev);
		if (err < 0) {
			list_del_init(&pcm->list);
			goto unlock;
		}

		for (substream = pcm->streams[cidx].substream; substream; substream = substream->next)
			snd_pcm_timer_init(substream);
	}

	pcm_call_notify(pcm, n_register);

 unlock:
	mutex_unlock(&register_mutex);
	return err;
}