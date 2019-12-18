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
struct snd_pcm_file {struct snd_pcm_substream* substream; } ;
struct snd_pcm {TYPE_1__* card; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  open_mutex; } ;
struct inode {int dummy; } ;
struct file {struct snd_pcm_file* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_file*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_card_file_remove (TYPE_1__*,struct file*) ; 
 int /*<<< orphan*/  snd_pcm_release_substream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_release(struct inode *inode, struct file *file)
{
	struct snd_pcm *pcm;
	struct snd_pcm_substream *substream;
	struct snd_pcm_file *pcm_file;

	pcm_file = file->private_data;
	substream = pcm_file->substream;
	if (snd_BUG_ON(!substream))
		return -ENXIO;
	pcm = substream->pcm;
	mutex_lock(&pcm->open_mutex);
	snd_pcm_release_substream(substream);
	kfree(pcm_file);
	mutex_unlock(&pcm->open_mutex);
	wake_up(&pcm->open_wait);
	module_put(pcm->card->module);
	snd_card_file_remove(pcm->card, file);
	return 0;
}