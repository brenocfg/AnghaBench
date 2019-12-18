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
struct wm_adsp_alg_region {scalar_t__ base; int /*<<< orphan*/  type; } ;
struct wm_coeff_ctl {scalar_t__ offset; struct wm_adsp_alg_region alg_region; struct wm_adsp* dsp; } ;
struct wm_adsp_region {int dummy; } ;
struct wm_adsp {TYPE_1__* ops; } ;
struct TYPE_2__ {unsigned int (* region_to_reg ) (struct wm_adsp_region const*,scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct wm_adsp_region const*,scalar_t__) ; 
 struct wm_adsp_region* wm_adsp_find_region (struct wm_adsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_coeff_base_reg(struct wm_coeff_ctl *ctl, unsigned int *reg)
{
	const struct wm_adsp_alg_region *alg_region = &ctl->alg_region;
	struct wm_adsp *dsp = ctl->dsp;
	const struct wm_adsp_region *mem;

	mem = wm_adsp_find_region(dsp, alg_region->type);
	if (!mem) {
		adsp_err(dsp, "No base for region %x\n",
			 alg_region->type);
		return -EINVAL;
	}

	*reg = dsp->ops->region_to_reg(mem, ctl->alg_region.base + ctl->offset);

	return 0;
}