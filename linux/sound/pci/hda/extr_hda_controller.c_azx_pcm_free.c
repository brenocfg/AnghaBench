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
struct snd_pcm {struct azx_pcm* private_data; } ;
struct azx_pcm {TYPE_1__* info; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct azx_pcm*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void azx_pcm_free(struct snd_pcm *pcm)
{
	struct azx_pcm *apcm = pcm->private_data;
	if (apcm) {
		list_del(&apcm->list);
		apcm->info->pcm = NULL;
		kfree(apcm);
	}
}