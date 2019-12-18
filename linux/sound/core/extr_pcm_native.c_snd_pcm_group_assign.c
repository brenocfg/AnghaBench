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
struct snd_pcm_substream {int /*<<< orphan*/  link_list; struct snd_pcm_group* group; } ;
struct snd_pcm_group {int /*<<< orphan*/  substreams; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_pcm_group_assign(struct snd_pcm_substream *substream,
				 struct snd_pcm_group *new_group)
{
	substream->group = new_group;
	list_move(&substream->link_list, &new_group->substreams);
}