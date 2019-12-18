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
struct axg_pdm {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 unsigned int GENMASK (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDM_CTRL ; 
 int PDM_CTRL_CHAN_EN (unsigned int) ; 
 int PDM_CTRL_CHAN_EN_MASK ; 
 int PDM_CTRL_CHAN_RSTN (unsigned int) ; 
 int PDM_CTRL_CHAN_RSTN_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void axg_pdm_set_channel_mask(struct axg_pdm *priv,
				     unsigned int channels)
{
	unsigned int mask = GENMASK(channels - 1, 0);

	/* Put all channel in reset */
	regmap_update_bits(priv->map, PDM_CTRL,
			   PDM_CTRL_CHAN_RSTN_MASK, 0);

	/* Take the necessary channels out of reset and enable them */
	regmap_update_bits(priv->map, PDM_CTRL,
			   PDM_CTRL_CHAN_RSTN_MASK |
			   PDM_CTRL_CHAN_EN_MASK,
			   PDM_CTRL_CHAN_RSTN(mask) |
			   PDM_CTRL_CHAN_EN(mask));
}