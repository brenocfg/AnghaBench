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
struct snd_pcm {struct pcm_runtime* private_data; } ;
struct pcm_runtime {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  hiface_pcm_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hiface_pcm_free(struct snd_pcm *pcm)
{
	struct pcm_runtime *rt = pcm->private_data;

	if (rt)
		hiface_pcm_destroy(rt->chip);
}