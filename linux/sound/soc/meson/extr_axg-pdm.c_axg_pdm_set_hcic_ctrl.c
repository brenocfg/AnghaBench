#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct axg_pdm_hcic {int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  ds; int /*<<< orphan*/  steps; } ;
struct axg_pdm {int /*<<< orphan*/  map; TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* filters; } ;
struct TYPE_3__ {struct axg_pdm_hcic hcic; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDM_HCIC_CTRL1 ; 
 unsigned int PDM_HCIC_CTRL1_DSR (int /*<<< orphan*/ ) ; 
 int PDM_HCIC_CTRL1_DSR_MASK ; 
 unsigned int PDM_HCIC_CTRL1_GAIN_MULT (int /*<<< orphan*/ ) ; 
 int PDM_HCIC_CTRL1_GAIN_MULT_MASK ; 
 unsigned int PDM_HCIC_CTRL1_GAIN_SFT (int /*<<< orphan*/ ) ; 
 int PDM_HCIC_CTRL1_GAIN_SFT_MASK ; 
 unsigned int PDM_HCIC_CTRL1_STAGE_NUM (int /*<<< orphan*/ ) ; 
 int PDM_HCIC_CTRL1_STAGE_NUM_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void axg_pdm_set_hcic_ctrl(struct axg_pdm *priv)
{
	const struct axg_pdm_hcic *hcic = &priv->cfg->filters->hcic;
	unsigned int val;

	val = PDM_HCIC_CTRL1_STAGE_NUM(hcic->steps);
	val |= PDM_HCIC_CTRL1_DSR(hcic->ds);
	val |= PDM_HCIC_CTRL1_GAIN_MULT(hcic->mult);
	val |= PDM_HCIC_CTRL1_GAIN_SFT(hcic->shift);

	regmap_update_bits(priv->map, PDM_HCIC_CTRL1,
			   PDM_HCIC_CTRL1_STAGE_NUM_MASK |
			   PDM_HCIC_CTRL1_DSR_MASK |
			   PDM_HCIC_CTRL1_GAIN_MULT_MASK |
			   PDM_HCIC_CTRL1_GAIN_SFT_MASK,
			   val);
}