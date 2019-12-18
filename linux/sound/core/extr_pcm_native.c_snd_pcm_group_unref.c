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
struct snd_pcm_substream {TYPE_1__* pcm; } ;
struct snd_pcm_group {int /*<<< orphan*/  refs; } ;
struct TYPE_2__ {int /*<<< orphan*/  nonatomic; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_pcm_group*) ; 
 int refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_group_unlock (struct snd_pcm_group*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_pcm_group_unref(struct snd_pcm_group *group,
				struct snd_pcm_substream *substream)
{
	bool do_free;

	if (!group)
		return;
	do_free = refcount_dec_and_test(&group->refs);
	snd_pcm_group_unlock(group, substream->pcm->nonatomic);
	if (do_free)
		kfree(group);
}