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
 int snd_pcm_action (struct action_ops const*,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_action_lock_irq(const struct action_ops *ops,
				   struct snd_pcm_substream *substream,
				   int state)
{
	int res;

	snd_pcm_stream_lock_irq(substream);
	res = snd_pcm_action(ops, substream, state);
	snd_pcm_stream_unlock_irq(substream);
	return res;
}