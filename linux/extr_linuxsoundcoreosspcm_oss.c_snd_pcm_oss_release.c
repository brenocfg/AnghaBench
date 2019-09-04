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
struct snd_pcm_substream {struct snd_pcm* pcm; } ;
struct snd_pcm_oss_file {struct snd_pcm_substream** streams; } ;
struct snd_pcm {TYPE_1__* card; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  open_mutex; } ;
struct inode {int dummy; } ;
struct file {struct snd_pcm_oss_file* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; int /*<<< orphan*/  shutdown; } ;

/* Variables and functions */
 int ENXIO ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_card_file_remove (TYPE_1__*,struct file*) ; 
 int /*<<< orphan*/  snd_pcm_oss_release_file (struct snd_pcm_oss_file*) ; 
 int /*<<< orphan*/  snd_pcm_oss_sync (struct snd_pcm_oss_file*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_oss_release(struct inode *inode, struct file *file)
{
	struct snd_pcm *pcm;
	struct snd_pcm_substream *substream;
	struct snd_pcm_oss_file *pcm_oss_file;

	pcm_oss_file = file->private_data;
	substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_PLAYBACK];
	if (substream == NULL)
		substream = pcm_oss_file->streams[SNDRV_PCM_STREAM_CAPTURE];
	if (snd_BUG_ON(!substream))
		return -ENXIO;
	pcm = substream->pcm;
	if (!pcm->card->shutdown)
		snd_pcm_oss_sync(pcm_oss_file);
	mutex_lock(&pcm->open_mutex);
	snd_pcm_oss_release_file(pcm_oss_file);
	mutex_unlock(&pcm->open_mutex);
	wake_up(&pcm->open_wait);
	module_put(pcm->card->module);
	snd_card_file_remove(pcm->card, file);
	return 0;
}