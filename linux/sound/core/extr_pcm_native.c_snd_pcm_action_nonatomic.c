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
struct action_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int snd_pcm_action_group (struct action_ops const*,struct snd_pcm_substream*,int,int /*<<< orphan*/ ) ; 
 int snd_pcm_action_single (struct action_ops const*,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_link_rwsem ; 
 scalar_t__ snd_pcm_stream_linked (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_action_nonatomic(const struct action_ops *ops,
				    struct snd_pcm_substream *substream,
				    int state)
{
	int res;

	/* Guarantee the group members won't change during non-atomic action */
	down_read(&snd_pcm_link_rwsem);
	if (snd_pcm_stream_linked(substream))
		res = snd_pcm_action_group(ops, substream, state, 0);
	else
		res = snd_pcm_action_single(ops, substream, state);
	up_read(&snd_pcm_link_rwsem);
	return res;
}