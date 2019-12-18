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
struct jz4740_i2s {int /*<<< orphan*/  clk_i2s; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  JZ4740_I2S_CLKSRC_EXT 129 
#define  JZ4740_I2S_CLKSRC_PLL 128 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,struct clk*) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct jz4740_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int jz4740_i2s_set_sysclk(struct snd_soc_dai *dai, int clk_id,
	unsigned int freq, int dir)
{
	struct jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	struct clk *parent;
	int ret = 0;

	switch (clk_id) {
	case JZ4740_I2S_CLKSRC_EXT:
		parent = clk_get(NULL, "ext");
		clk_set_parent(i2s->clk_i2s, parent);
		break;
	case JZ4740_I2S_CLKSRC_PLL:
		parent = clk_get(NULL, "pll half");
		clk_set_parent(i2s->clk_i2s, parent);
		ret = clk_set_rate(i2s->clk_i2s, freq);
		break;
	default:
		return -EINVAL;
	}
	clk_put(parent);

	return ret;
}