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
#define  WMFW_ADSP1_DM 132 
#define  WMFW_ADSP1_PM 131 
#define  WMFW_ADSP1_ZM 130 
#define  WMFW_ADSP2_XM 129 
#define  WMFW_ADSP2_YM 128 

__attribute__((used)) static unsigned int wm_adsp_region_to_reg(struct wm_adsp_region const *mem,
					  unsigned int offset)
{
	switch (mem->type) {
	case WMFW_ADSP1_PM:
		return mem->base + (offset * 3);
	case WMFW_ADSP1_DM:
	case WMFW_ADSP2_XM:
	case WMFW_ADSP2_YM:
	case WMFW_ADSP1_ZM:
		return mem->base + (offset * 2);
	default:
		WARN(1, "Unknown memory region type");
		return offset;
	}
}