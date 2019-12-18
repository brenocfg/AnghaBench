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
struct snd_pcm_substream {int number; int ref_count; int f_flags; int /*<<< orphan*/  pid; int /*<<< orphan*/  private_data; struct snd_pcm_runtime* runtime; struct snd_pcm_substream* next; } ;
struct snd_pcm_str {int substream_count; int /*<<< orphan*/  substream_opened; struct snd_pcm_substream* substream; } ;
struct snd_pcm_runtime {TYPE_1__* status; int /*<<< orphan*/  tsleep; int /*<<< orphan*/  sleep; TYPE_1__* control; } ;
struct snd_pcm_mmap_status {int dummy; } ;
struct snd_pcm_mmap_control {int dummy; } ;
struct snd_pcm {int info_flags; int /*<<< orphan*/  private_data; struct snd_pcm_str* streams; struct snd_card* card; } ;
struct snd_card {int dummy; } ;
struct file {int f_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADFD ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int O_APPEND ; 
 size_t PAGE_ALIGN (int) ; 
 int SNDRV_PCM_INFO_HALF_DUPLEX ; 
 int /*<<< orphan*/  SNDRV_PCM_STATE_OPEN ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SND_CTL_SUBDEV_PCM ; 
 scalar_t__ SUBSTREAM_BUSY (struct snd_pcm_substream*) ; 
 void* alloc_pages_exact (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  free_pages_exact (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_runtime*) ; 
 struct snd_pcm_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_get_preferred_subdevice (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

int snd_pcm_attach_substream(struct snd_pcm *pcm, int stream,
			     struct file *file,
			     struct snd_pcm_substream **rsubstream)
{
	struct snd_pcm_str * pstr;
	struct snd_pcm_substream *substream;
	struct snd_pcm_runtime *runtime;
	struct snd_card *card;
	int prefer_subdevice;
	size_t size;

	if (snd_BUG_ON(!pcm || !rsubstream))
		return -ENXIO;
	if (snd_BUG_ON(stream != SNDRV_PCM_STREAM_PLAYBACK &&
		       stream != SNDRV_PCM_STREAM_CAPTURE))
		return -EINVAL;
	*rsubstream = NULL;
	pstr = &pcm->streams[stream];
	if (pstr->substream == NULL || pstr->substream_count == 0)
		return -ENODEV;

	card = pcm->card;
	prefer_subdevice = snd_ctl_get_preferred_subdevice(card, SND_CTL_SUBDEV_PCM);

	if (pcm->info_flags & SNDRV_PCM_INFO_HALF_DUPLEX) {
		int opposite = !stream;

		for (substream = pcm->streams[opposite].substream; substream;
		     substream = substream->next) {
			if (SUBSTREAM_BUSY(substream))
				return -EAGAIN;
		}
	}

	if (file->f_flags & O_APPEND) {
		if (prefer_subdevice < 0) {
			if (pstr->substream_count > 1)
				return -EINVAL; /* must be unique */
			substream = pstr->substream;
		} else {
			for (substream = pstr->substream; substream;
			     substream = substream->next)
				if (substream->number == prefer_subdevice)
					break;
		}
		if (! substream)
			return -ENODEV;
		if (! SUBSTREAM_BUSY(substream))
			return -EBADFD;
		substream->ref_count++;
		*rsubstream = substream;
		return 0;
	}

	for (substream = pstr->substream; substream; substream = substream->next) {
		if (!SUBSTREAM_BUSY(substream) &&
		    (prefer_subdevice == -1 ||
		     substream->number == prefer_subdevice))
			break;
	}
	if (substream == NULL)
		return -EAGAIN;

	runtime = kzalloc(sizeof(*runtime), GFP_KERNEL);
	if (runtime == NULL)
		return -ENOMEM;

	size = PAGE_ALIGN(sizeof(struct snd_pcm_mmap_status));
	runtime->status = alloc_pages_exact(size, GFP_KERNEL);
	if (runtime->status == NULL) {
		kfree(runtime);
		return -ENOMEM;
	}
	memset(runtime->status, 0, size);

	size = PAGE_ALIGN(sizeof(struct snd_pcm_mmap_control));
	runtime->control = alloc_pages_exact(size, GFP_KERNEL);
	if (runtime->control == NULL) {
		free_pages_exact(runtime->status,
			       PAGE_ALIGN(sizeof(struct snd_pcm_mmap_status)));
		kfree(runtime);
		return -ENOMEM;
	}
	memset(runtime->control, 0, size);

	init_waitqueue_head(&runtime->sleep);
	init_waitqueue_head(&runtime->tsleep);

	runtime->status->state = SNDRV_PCM_STATE_OPEN;

	substream->runtime = runtime;
	substream->private_data = pcm->private_data;
	substream->ref_count = 1;
	substream->f_flags = file->f_flags;
	substream->pid = get_pid(task_pid(current));
	pstr->substream_opened++;
	*rsubstream = substream;
	return 0;
}