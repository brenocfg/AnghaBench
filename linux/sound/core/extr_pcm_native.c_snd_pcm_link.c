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
struct snd_pcm_substream {struct snd_pcm_group* group; TYPE_3__* pcm; TYPE_2__* runtime; } ;
struct snd_pcm_group {int /*<<< orphan*/  refs; } ;
struct snd_pcm_file {struct snd_pcm_substream* substream; } ;
struct fd {TYPE_4__* file; } ;
struct TYPE_8__ {struct snd_pcm_file* private_data; } ;
struct TYPE_7__ {int nonatomic; } ;
struct TYPE_6__ {TYPE_1__* status; } ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 int EALREADY ; 
 int EBADFD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SNDRV_PCM_STATE_OPEN ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  is_pcm_file (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct snd_pcm_group*) ; 
 struct snd_pcm_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_group_assign (struct snd_pcm_substream*,struct snd_pcm_group*) ; 
 int /*<<< orphan*/  snd_pcm_group_init (struct snd_pcm_group*) ; 
 int /*<<< orphan*/  snd_pcm_group_lock_irq (struct snd_pcm_group*,int) ; 
 int /*<<< orphan*/  snd_pcm_group_unlock_irq (struct snd_pcm_group*,int) ; 
 int /*<<< orphan*/  snd_pcm_link_rwsem ; 
 scalar_t__ snd_pcm_stream_linked (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_link(struct snd_pcm_substream *substream, int fd)
{
	int res = 0;
	struct snd_pcm_file *pcm_file;
	struct snd_pcm_substream *substream1;
	struct snd_pcm_group *group, *target_group;
	bool nonatomic = substream->pcm->nonatomic;
	struct fd f = fdget(fd);

	if (!f.file)
		return -EBADFD;
	if (!is_pcm_file(f.file)) {
		res = -EBADFD;
		goto _badf;
	}
	pcm_file = f.file->private_data;
	substream1 = pcm_file->substream;
	group = kzalloc(sizeof(*group), GFP_KERNEL);
	if (!group) {
		res = -ENOMEM;
		goto _nolock;
	}
	snd_pcm_group_init(group);

	down_write(&snd_pcm_link_rwsem);
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

	snd_pcm_stream_lock_irq(substream);
	if (!snd_pcm_stream_linked(substream)) {
		snd_pcm_group_assign(substream, group);
		group = NULL; /* assigned, don't free this one below */
	}
	target_group = substream->group;
	snd_pcm_stream_unlock_irq(substream);

	snd_pcm_group_lock_irq(target_group, nonatomic);
	snd_pcm_stream_lock(substream1);
	snd_pcm_group_assign(substream1, target_group);
	refcount_inc(&target_group->refs);
	snd_pcm_stream_unlock(substream1);
	snd_pcm_group_unlock_irq(target_group, nonatomic);
 _end:
	up_write(&snd_pcm_link_rwsem);
 _nolock:
	kfree(group);
 _badf:
	fdput(f);
	return res;
}