#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; } ;
struct snd_pcm_substream {TYPE_3__* group; TYPE_2__ self_group; TYPE_1__* pcm; } ;
struct action_ops {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {scalar_t__ nonatomic; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_action_group (struct action_ops const*,struct snd_pcm_substream*,int,int) ; 
 int snd_pcm_action_single (struct action_ops const*,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_stream_linked (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_action(const struct action_ops *ops,
			  struct snd_pcm_substream *substream,
			  int state)
{
	int res;

	if (!snd_pcm_stream_linked(substream))
		return snd_pcm_action_single(ops, substream, state);

	if (substream->pcm->nonatomic) {
		if (!mutex_trylock(&substream->group->mutex)) {
			mutex_unlock(&substream->self_group.mutex);
			mutex_lock(&substream->group->mutex);
			mutex_lock(&substream->self_group.mutex);
		}
		res = snd_pcm_action_group(ops, substream, state, 1);
		mutex_unlock(&substream->group->mutex);
	} else {
		if (!spin_trylock(&substream->group->lock)) {
			spin_unlock(&substream->self_group.lock);
			spin_lock(&substream->group->lock);
			spin_lock(&substream->self_group.lock);
		}
		res = snd_pcm_action_group(ops, substream, state, 1);
		spin_unlock(&substream->group->lock);
	}
	return res;
}