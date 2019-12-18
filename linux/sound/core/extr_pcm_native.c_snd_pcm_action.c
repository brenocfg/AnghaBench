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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_group {int dummy; } ;
struct action_ops {int dummy; } ;

/* Variables and functions */
 int snd_pcm_action_group (struct action_ops const*,struct snd_pcm_substream*,int,int) ; 
 int snd_pcm_action_single (struct action_ops const*,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_group_unref (struct snd_pcm_group*,struct snd_pcm_substream*) ; 
 struct snd_pcm_group* snd_pcm_stream_group_ref (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_action(const struct action_ops *ops,
			  struct snd_pcm_substream *substream,
			  int state)
{
	struct snd_pcm_group *group;
	int res;

	group = snd_pcm_stream_group_ref(substream);
	if (group)
		res = snd_pcm_action_group(ops, substream, state, 1);
	else
		res = snd_pcm_action_single(ops, substream, state);
	snd_pcm_group_unref(group, substream);
	return res;
}