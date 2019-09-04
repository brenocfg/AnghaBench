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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct mxs_saif {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct mxs_saif* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void mxs_saif_shutdown(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *cpu_dai)
{
	struct mxs_saif *saif = snd_soc_dai_get_drvdata(cpu_dai);

	clk_unprepare(saif->clk);
}