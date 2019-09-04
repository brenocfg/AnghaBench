#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_3__* pcm; struct snd_pcm_group* group; int /*<<< orphan*/  link_list; TYPE_2__* runtime; } ;
struct snd_pcm_group {int count; int /*<<< orphan*/  substreams; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;
struct snd_pcm_file {struct snd_pcm_substream* substream; } ;
struct fd {TYPE_4__* file; } ;
struct TYPE_8__ {struct snd_pcm_file* private_data; } ;
struct TYPE_7__ {scalar_t__ nonatomic; int /*<<< orphan*/  card; } ;
struct TYPE_6__ {TYPE_1__* status; } ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 int EALREADY ; 
 int EBADFD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 int /*<<< orphan*/  down_write_nonfifo (int /*<<< orphan*/ *) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  is_pcm_file (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_group*) ; 
 struct snd_pcm_group* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_link_rwlock ; 
 int /*<<< orphan*/  snd_pcm_link_rwsem ; 
 scalar_t__ snd_pcm_stream_linked (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_link(struct snd_pcm_substream *substream, int fd)
{
	int res = 0;
	struct snd_pcm_file *pcm_file;
	struct snd_pcm_substream *substream1;
	struct snd_pcm_group *group;
	struct fd f = fdget(fd);

	if (!f.file)
		return -EBADFD;
	if (!is_pcm_file(f.file)) {
		res = -EBADFD;
		goto _badf;
	}
	pcm_file = f.file->private_data;
	substream1 = pcm_file->substream;
	group = kmalloc(sizeof(*group), GFP_KERNEL);
	if (!group) {
		res = -ENOMEM;
		goto _nolock;
	}
	down_write_nonfifo(&snd_pcm_link_rwsem);
	write_lock_irq(&snd_pcm_link_rwlock);
	if (substream->runtime->status->state == SNDRV_PCM_STATE_OPEN ||
	    substream->runtime->status->state != substream1->runtime->status->state ||
	    substream->pcm->nonatomic != substream1->pcm->nonatomic) {
		res = -EBADFD;
		goto _end;
	}
	if (snd_pcm_stream_linked(substream1)) {
		res = -EALREADY;
		goto _end;
	}
	if (!snd_pcm_stream_linked(substream)) {
		substream->group = group;
		group = NULL;
		spin_lock_init(&substream->group->lock);
		mutex_init(&substream->group->mutex);
		INIT_LIST_HEAD(&substream->group->substreams);
		list_add_tail(&substream->link_list, &substream->group->substreams);
		substream->group->count = 1;
	}
	list_add_tail(&substream1->link_list, &substream->group->substreams);
	substream->group->count++;
	substream1->group = substream->group;
 _end:
	write_unlock_irq(&snd_pcm_link_rwlock);
	up_write(&snd_pcm_link_rwsem);
 _nolock:
	snd_card_unref(substream1->pcm->card);
	kfree(group);
 _badf:
	fdput(f);
	return res;
}