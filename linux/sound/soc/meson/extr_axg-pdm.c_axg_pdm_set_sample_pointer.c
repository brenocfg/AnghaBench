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
typedef  int /*<<< orphan*/  u64 ;
struct axg_pdm {int /*<<< orphan*/  map; int /*<<< orphan*/  dclk; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PDM_CHAN_CTRL ; 
 int /*<<< orphan*/  PDM_CHAN_CTRL1 ; 
 int PDM_CHAN_CTRL_NUM ; 
 unsigned int PDM_CHAN_CTRL_POINTER_MAX ; 
 int PDM_CHAN_CTRL_POINTER_WIDTH ; 
 scalar_t__ WARN_ON (int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int axg_pdm_set_sample_pointer(struct axg_pdm *priv)
{
	unsigned int spmax, sp, val;
	int i;

	/* Max sample counter value per half period of dclk */
	spmax = DIV_ROUND_UP_ULL((u64)clk_get_rate(priv->sysclk),
				 clk_get_rate(priv->dclk) * 2);

	/* Check if sysclk is not too fast - should not happen */
	if (WARN_ON(spmax > PDM_CHAN_CTRL_POINTER_MAX))
		return -EINVAL;

	/* Capture the data when we are at 75% of the half period */
	sp = spmax * 3 / 4;

	for (i = 0, val = 0; i < PDM_CHAN_CTRL_NUM; i++)
		val |= sp << (PDM_CHAN_CTRL_POINTER_WIDTH * i);

	regmap_write(priv->map, PDM_CHAN_CTRL, val);
	regmap_write(priv->map, PDM_CHAN_CTRL1, val);

	return 0;
}