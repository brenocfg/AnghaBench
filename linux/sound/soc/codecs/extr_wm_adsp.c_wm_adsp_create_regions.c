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
struct wm_adsp_alg_region {int dummy; } ;
struct wm_adsp {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct wm_adsp_alg_region*) ; 
 int PTR_ERR (struct wm_adsp_alg_region*) ; 
 struct wm_adsp_alg_region* wm_adsp_create_region (struct wm_adsp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_adsp_create_regions(struct wm_adsp *dsp, __be32 id, int nregions,
				int *type, __be32 *base)
{
	struct wm_adsp_alg_region *alg_region;
	int i;

	for (i = 0; i < nregions; i++) {
		alg_region = wm_adsp_create_region(dsp, type[i], id, base[i]);
		if (IS_ERR(alg_region))
			return PTR_ERR(alg_region);
	}

	return 0;
}