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
struct wm_adsp_alg_region {int type; int /*<<< orphan*/  list; void* base; void* alg; } ;
struct wm_adsp {scalar_t__ fw_ver; int /*<<< orphan*/  alg_regions; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct wm_adsp_alg_region* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct wm_adsp_alg_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm_adsp_ctl_fixup_base (struct wm_adsp*,struct wm_adsp_alg_region*) ; 

__attribute__((used)) static struct wm_adsp_alg_region *wm_adsp_create_region(struct wm_adsp *dsp,
							int type, __be32 id,
							__be32 base)
{
	struct wm_adsp_alg_region *alg_region;

	alg_region = kzalloc(sizeof(*alg_region), GFP_KERNEL);
	if (!alg_region)
		return ERR_PTR(-ENOMEM);

	alg_region->type = type;
	alg_region->alg = be32_to_cpu(id);
	alg_region->base = be32_to_cpu(base);

	list_add_tail(&alg_region->list, &dsp->alg_regions);

	if (dsp->fw_ver > 0)
		wm_adsp_ctl_fixup_base(dsp, alg_region);

	return alg_region;
}