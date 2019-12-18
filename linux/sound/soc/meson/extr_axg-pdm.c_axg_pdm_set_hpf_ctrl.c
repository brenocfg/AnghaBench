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
struct axg_pdm_hpf {int /*<<< orphan*/  steps; int /*<<< orphan*/  out_factor; } ;
struct axg_pdm {int /*<<< orphan*/  map; TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* filters; } ;
struct TYPE_3__ {struct axg_pdm_hpf hpf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDM_HPF_CTRL ; 
 unsigned int PDM_HPF_OUT_FACTOR (int /*<<< orphan*/ ) ; 
 int PDM_HPF_OUT_FACTOR_MASK ; 
 unsigned int PDM_HPF_SFT_STEPS (int /*<<< orphan*/ ) ; 
 int PDM_HPF_SFT_STEPS_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void axg_pdm_set_hpf_ctrl(struct axg_pdm *priv)
{
	const struct axg_pdm_hpf *hpf = &priv->cfg->filters->hpf;
	unsigned int val;

	val = PDM_HPF_OUT_FACTOR(hpf->out_factor);
	val |= PDM_HPF_SFT_STEPS(hpf->steps);

	regmap_update_bits(priv->map, PDM_HPF_CTRL,
			   PDM_HPF_OUT_FACTOR_MASK |
			   PDM_HPF_SFT_STEPS_MASK,
			   val);
}