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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_emu8k_pcm {int dummy; } ;
struct TYPE_2__ {struct snd_emu8k_pcm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_emu8k_pcm*) ; 

__attribute__((used)) static int emu8k_pcm_close(struct snd_pcm_substream *subs)
{
	struct snd_emu8k_pcm *rec = subs->runtime->private_data;
	kfree(rec);
	subs->runtime->private_data = NULL;
	return 0;
}