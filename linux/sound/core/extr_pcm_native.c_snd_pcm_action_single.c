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
struct action_ops {int (* pre_action ) (struct snd_pcm_substream*,int) ;int (* do_action ) (struct snd_pcm_substream*,int) ;int /*<<< orphan*/  (* undo_action ) (struct snd_pcm_substream*,int) ;int /*<<< orphan*/  (* post_action ) (struct snd_pcm_substream*,int) ;} ;

/* Variables and functions */
 int stub1 (struct snd_pcm_substream*,int) ; 
 int stub2 (struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  stub3 (struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  stub4 (struct snd_pcm_substream*,int) ; 

__attribute__((used)) static int snd_pcm_action_single(const struct action_ops *ops,
				 struct snd_pcm_substream *substream,
				 int state)
{
	int res;
	
	res = ops->pre_action(substream, state);
	if (res < 0)
		return res;
	res = ops->do_action(substream, state);
	if (res == 0)
		ops->post_action(substream, state);
	else if (ops->undo_action)
		ops->undo_action(substream, state);
	return res;
}