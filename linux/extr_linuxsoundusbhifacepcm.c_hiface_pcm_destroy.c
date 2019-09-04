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
struct pcm_runtime {TYPE_1__* out_urbs; } ;
struct hiface_chip {struct pcm_runtime* pcm; } ;
struct TYPE_2__ {struct pcm_runtime* buffer; } ;

/* Variables and functions */
 int PCM_N_URBS ; 
 int /*<<< orphan*/  kfree (struct pcm_runtime*) ; 

__attribute__((used)) static void hiface_pcm_destroy(struct hiface_chip *chip)
{
	struct pcm_runtime *rt = chip->pcm;
	int i;

	for (i = 0; i < PCM_N_URBS; i++)
		kfree(rt->out_urbs[i].buffer);

	kfree(chip->pcm);
	chip->pcm = NULL;
}