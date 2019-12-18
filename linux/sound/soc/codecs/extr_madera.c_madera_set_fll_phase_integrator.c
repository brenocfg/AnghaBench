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
struct madera_fll_cfg {scalar_t__ theta; } ;
struct madera_fll {scalar_t__ base; TYPE_1__* madera; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int MADERA_FLL1_PHASE_ENA_MASK ; 
 int MADERA_FLL1_PHASE_ENA_SHIFT ; 
 int MADERA_FLL1_PHASE_GAIN_MASK ; 
 int MADERA_FLL1_PHASE_GAIN_SHIFT ; 
 scalar_t__ MADERA_FLL_EFS_2_OFFS ; 
 int /*<<< orphan*/  regmap_update_bits_check (int /*<<< orphan*/ ,scalar_t__,int,unsigned int,int*) ; 

__attribute__((used)) static bool madera_set_fll_phase_integrator(struct madera_fll *fll,
					    struct madera_fll_cfg *ref_cfg,
					    bool sync)
{
	unsigned int val;
	bool reg_change;

	if (!sync && ref_cfg->theta == 0)
		val = (1 << MADERA_FLL1_PHASE_ENA_SHIFT) |
		      (2 << MADERA_FLL1_PHASE_GAIN_SHIFT);
	else
		val = 2 << MADERA_FLL1_PHASE_GAIN_SHIFT;

	regmap_update_bits_check(fll->madera->regmap,
				 fll->base + MADERA_FLL_EFS_2_OFFS,
				 MADERA_FLL1_PHASE_ENA_MASK |
				 MADERA_FLL1_PHASE_GAIN_MASK,
				 val, &reg_change);

	return reg_change;
}