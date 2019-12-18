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
struct wm_adsp_region {int type; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
#define  WMFW_ADSP2_XM 132 
#define  WMFW_ADSP2_YM 131 
#define  WMFW_HALO_PM_PACKED 130 
#define  WMFW_HALO_XM_PACKED 129 
#define  WMFW_HALO_YM_PACKED 128 

__attribute__((used)) static unsigned int wm_halo_region_to_reg(struct wm_adsp_region const *mem,
					  unsigned int offset)
{
	switch (mem->type) {
	case WMFW_ADSP2_XM:
	case WMFW_ADSP2_YM:
		return mem->base + (offset * 4);
	case WMFW_HALO_XM_PACKED:
	case WMFW_HALO_YM_PACKED:
		return (mem->base + (offset * 3)) & ~0x3;
	case WMFW_HALO_PM_PACKED:
		return mem->base + (offset * 5);
	default:
		WARN(1, "Unknown memory region type");
		return offset;
	}
}