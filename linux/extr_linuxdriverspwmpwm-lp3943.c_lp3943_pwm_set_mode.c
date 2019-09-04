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
typedef  int u8 ;
struct lp3943_reg_cfg {int shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct lp3943_pwm_map {int num_outputs; int* output; } ;
struct lp3943_pwm {struct lp3943* lp3943; } ;
struct lp3943 {struct lp3943_reg_cfg* mux_cfg; } ;

/* Variables and functions */
 int lp3943_update_bits (struct lp3943*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lp3943_pwm_set_mode(struct lp3943_pwm *lp3943_pwm,
			       struct lp3943_pwm_map *pwm_map,
			       u8 val)
{
	struct lp3943 *lp3943 = lp3943_pwm->lp3943;
	const struct lp3943_reg_cfg *mux = lp3943->mux_cfg;
	int i, index, err;

	for (i = 0; i < pwm_map->num_outputs; i++) {
		index = pwm_map->output[i];
		err = lp3943_update_bits(lp3943, mux[index].reg,
					 mux[index].mask,
					 val << mux[index].shift);
		if (err)
			return err;
	}

	return 0;
}