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
struct ath10k_wcn3990_vreg_info {int /*<<< orphan*/  max_v; int /*<<< orphan*/  reg; scalar_t__ settle_delay; int /*<<< orphan*/  name; scalar_t__ load_ua; int /*<<< orphan*/  min_v; } ;
struct ath10k_snoc {struct ath10k_wcn3990_vreg_info* vreg; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH10K_DBG_SNOC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int /*<<< orphan*/ ,...) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_set_load (int /*<<< orphan*/ ,scalar_t__) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 
 int /*<<< orphan*/  vreg_cfg ; 

__attribute__((used)) static int ath10k_wcn3990_vreg_on(struct ath10k *ar)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct ath10k_wcn3990_vreg_info *vreg_info;
	int ret = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(vreg_cfg); i++) {
		vreg_info = &ar_snoc->vreg[i];

		if (!vreg_info->reg)
			continue;

		ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc regulator %s being enabled\n",
			   vreg_info->name);

		ret = regulator_set_voltage(vreg_info->reg, vreg_info->min_v,
					    vreg_info->max_v);
		if (ret) {
			ath10k_err(ar,
				   "failed to set regulator %s voltage-min: %d voltage-max: %d\n",
				   vreg_info->name, vreg_info->min_v, vreg_info->max_v);
			goto err_reg_config;
		}

		if (vreg_info->load_ua) {
			ret = regulator_set_load(vreg_info->reg,
						 vreg_info->load_ua);
			if (ret < 0) {
				ath10k_err(ar,
					   "failed to set regulator %s load: %d\n",
					   vreg_info->name,
					   vreg_info->load_ua);
				goto err_reg_config;
			}
		}

		ret = regulator_enable(vreg_info->reg);
		if (ret) {
			ath10k_err(ar, "failed to enable regulator %s\n",
				   vreg_info->name);
			goto err_reg_config;
		}

		if (vreg_info->settle_delay)
			udelay(vreg_info->settle_delay);
	}

	return 0;

err_reg_config:
	for (; i >= 0; i--) {
		vreg_info = &ar_snoc->vreg[i];

		if (!vreg_info->reg)
			continue;

		regulator_disable(vreg_info->reg);
		regulator_set_load(vreg_info->reg, 0);
		regulator_set_voltage(vreg_info->reg, 0, vreg_info->max_v);
	}

	return ret;
}