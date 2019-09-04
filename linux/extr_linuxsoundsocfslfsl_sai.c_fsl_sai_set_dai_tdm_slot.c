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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int dummy; } ;
struct fsl_sai {int slots; int slot_width; } ;

/* Variables and functions */
 struct fsl_sai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_sai_set_dai_tdm_slot(struct snd_soc_dai *cpu_dai, u32 tx_mask,
				u32 rx_mask, int slots, int slot_width)
{
	struct fsl_sai *sai = snd_soc_dai_get_drvdata(cpu_dai);

	sai->slots = slots;
	sai->slot_width = slot_width;

	return 0;
}