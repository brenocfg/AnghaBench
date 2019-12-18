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
struct wm_adsp {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int WMFW_ADSP2_XM ; 
 int WMFW_ADSP2_YM ; 
 int WMFW_HALO_XM_PACKED ; 
 int WMFW_HALO_YM_PACKED ; 
 int wm_adsp_create_regions (struct wm_adsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wm_halo_create_regions(struct wm_adsp *dsp, __be32 id,
				  __be32 xm_base, __be32 ym_base)
{
	int types[] = {
		WMFW_ADSP2_XM, WMFW_HALO_XM_PACKED,
		WMFW_ADSP2_YM, WMFW_HALO_YM_PACKED
	};
	__be32 bases[] = { xm_base, xm_base, ym_base, ym_base };

	return wm_adsp_create_regions(dsp, id, ARRAY_SIZE(types), types, bases);
}