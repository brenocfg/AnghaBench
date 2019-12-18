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
struct axg_pdm_lpf {unsigned int tap_num; int /*<<< orphan*/ * tap; } ;
struct axg_pdm {int /*<<< orphan*/  map; TYPE_1__* cfg; } ;
struct TYPE_4__ {struct axg_pdm_lpf* lpf; } ;
struct TYPE_3__ {TYPE_2__* filters; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PDM_COEFF_ADDR ; 
 int /*<<< orphan*/  PDM_COEFF_DATA ; 
 unsigned int PDM_LPF_MAX_STAGE ; 
 int PDM_LPF_NUM ; 
 int /*<<< orphan*/  axg_pdm_set_lpf_ctrl (struct axg_pdm*,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_pdm_set_lpf_filters(struct axg_pdm *priv)
{
	const struct axg_pdm_lpf *lpf = priv->cfg->filters->lpf;
	unsigned int count = 0;
	int i, j;

	for (i = 0; i < PDM_LPF_NUM; i++)
		count += lpf[i].tap_num;

	/* Make sure the coeffs fit in the memory */
	if (count >= PDM_LPF_MAX_STAGE)
		return -EINVAL;

	/* Set the initial APB bus register address */
	regmap_write(priv->map, PDM_COEFF_ADDR, 0);

	/* Set the tap filter values of all 3 filters */
	for (i = 0; i < PDM_LPF_NUM; i++) {
		axg_pdm_set_lpf_ctrl(priv, i);

		for (j = 0; j < lpf[i].tap_num; j++)
			regmap_write(priv->map, PDM_COEFF_DATA, lpf[i].tap[j]);
	}

	return 0;
}