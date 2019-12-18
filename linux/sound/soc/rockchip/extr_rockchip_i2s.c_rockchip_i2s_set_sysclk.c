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
struct rk_i2s_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rk_i2s_dev* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static int rockchip_i2s_set_sysclk(struct snd_soc_dai *cpu_dai, int clk_id,
				   unsigned int freq, int dir)
{
	struct rk_i2s_dev *i2s = to_info(cpu_dai);
	int ret;

	if (freq == 0)
		return 0;

	ret = clk_set_rate(i2s->mclk, freq);
	if (ret)
		dev_err(i2s->dev, "Fail to set mclk %d\n", ret);

	return ret;
}