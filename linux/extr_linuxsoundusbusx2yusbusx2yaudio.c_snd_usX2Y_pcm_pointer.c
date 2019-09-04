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
struct snd_usX2Y_substream {int /*<<< orphan*/  hwptr_done; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {struct snd_usX2Y_substream* private_data; } ;

/* Variables and functions */

__attribute__((used)) static snd_pcm_uframes_t snd_usX2Y_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_usX2Y_substream *subs = substream->runtime->private_data;
	return subs->hwptr_done;
}