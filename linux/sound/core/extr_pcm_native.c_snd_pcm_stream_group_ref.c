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
struct snd_pcm_substream {struct snd_pcm_group* group; TYPE_1__* pcm; } ;
struct snd_pcm_group {int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  refs; } ;
struct TYPE_2__ {int nonatomic; } ;

/* Variables and functions */
 int mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_group_lock (struct snd_pcm_group*,int) ; 
 int /*<<< orphan*/  snd_pcm_group_unref (struct snd_pcm_group*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_linked (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock (struct snd_pcm_substream*) ; 
 int spin_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct snd_pcm_group *
snd_pcm_stream_group_ref(struct snd_pcm_substream *substream)
{
	bool nonatomic = substream->pcm->nonatomic;
	struct snd_pcm_group *group;
	bool trylock;

	for (;;) {
		if (!snd_pcm_stream_linked(substream))
			return NULL;
		group = substream->group;
		/* block freeing the group object */
		refcount_inc(&group->refs);

		trylock = nonatomic ? mutex_trylock(&group->mutex) :
			spin_trylock(&group->lock);
		if (trylock)
			break; /* OK */

		/* re-lock for avoiding ABBA deadlock */
		snd_pcm_stream_unlock(substream);
		snd_pcm_group_lock(group, nonatomic);
		snd_pcm_stream_lock(substream);

		/* check the group again; the above opens a small race window */
		if (substream->group == group)
			break; /* OK */
		/* group changed, try again */
		snd_pcm_group_unref(group, substream);
	}
	return group;
}