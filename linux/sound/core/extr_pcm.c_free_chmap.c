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
struct snd_pcm_str {int /*<<< orphan*/ * chmap_kctl; TYPE_1__* pcm; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ctl_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_chmap(struct snd_pcm_str *pstr)
{
	if (pstr->chmap_kctl) {
		snd_ctl_remove(pstr->pcm->card, pstr->chmap_kctl);
		pstr->chmap_kctl = NULL;
	}
}