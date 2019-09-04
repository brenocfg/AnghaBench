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
struct snd_soc_dai {TYPE_1__* driver; } ;
struct snd_pcm_substream {int dummy; } ;
struct lpass_data {int /*<<< orphan*/ * mi2s_osr_clk; int /*<<< orphan*/ * mi2s_bit_clk; } ;
struct TYPE_2__ {size_t id; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct lpass_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void lpass_cpu_daiops_shutdown(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(drvdata->mi2s_bit_clk[dai->driver->id]);

	clk_disable_unprepare(drvdata->mi2s_osr_clk[dai->driver->id]);
}