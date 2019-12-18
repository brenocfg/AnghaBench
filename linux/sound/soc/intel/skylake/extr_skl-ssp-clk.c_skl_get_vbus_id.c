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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
#define  SKL_MCLK 130 
#define  SKL_SCLK 129 
 int SKL_SCLKFS_OFS ; 
#define  SKL_SCLK_FS 128 
 int SKL_SCLK_OFS ; 

__attribute__((used)) static int skl_get_vbus_id(u32 index, u8 clk_type)
{
	switch (clk_type) {
	case SKL_MCLK:
		return index;

	case SKL_SCLK:
		return index - SKL_SCLK_OFS;

	case SKL_SCLK_FS:
		return index - SKL_SCLKFS_OFS;

	default:
		return -EINVAL;
	}
}