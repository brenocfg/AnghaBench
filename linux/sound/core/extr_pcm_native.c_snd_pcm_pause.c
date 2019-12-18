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

/* Variables and functions */
 int snd_pcm_action (int /*<<< orphan*/ *,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_action_pause ; 

__attribute__((used)) static int snd_pcm_pause(struct snd_pcm_substream *substream, int push)
{
	return snd_pcm_action(&snd_pcm_action_pause, substream, push);
}