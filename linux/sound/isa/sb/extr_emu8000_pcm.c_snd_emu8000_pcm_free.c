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
struct snd_pcm {struct snd_emu8000* private_data; } ;
struct snd_emu8000 {int /*<<< orphan*/ * pcm; } ;

/* Variables and functions */

__attribute__((used)) static void snd_emu8000_pcm_free(struct snd_pcm *pcm)
{
	struct snd_emu8000 *emu = pcm->private_data;
	emu->pcm = NULL;
}