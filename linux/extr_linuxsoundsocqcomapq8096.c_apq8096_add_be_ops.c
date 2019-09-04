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
struct snd_soc_dai_link {int no_pcm; int /*<<< orphan*/  be_hw_params_fixup; } ;
struct snd_soc_card {int num_links; struct snd_soc_dai_link* dai_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  apq8096_be_hw_params_fixup ; 

__attribute__((used)) static void apq8096_add_be_ops(struct snd_soc_card *card)
{
	struct snd_soc_dai_link *link = card->dai_link;
	int i, num_links = card->num_links;

	for (i = 0; i < num_links; i++) {
		if (link->no_pcm == 1)
			link->be_hw_params_fixup = apq8096_be_hw_params_fixup;
		link++;
	}
}