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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct nau8810 {int clk_id; unsigned int sysclk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NAU8810_SCLK_PLL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,char*) ; 
 struct nau8810* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int nau8810_set_sysclk(struct snd_soc_dai *dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct nau8810 *nau8810 = snd_soc_component_get_drvdata(component);

	nau8810->clk_id = clk_id;
	nau8810->sysclk = freq;
	dev_dbg(nau8810->dev, "master sysclk %dHz, source %s\n",
		freq, clk_id == NAU8810_SCLK_PLL ? "PLL" : "MCLK");

	return 0;
}