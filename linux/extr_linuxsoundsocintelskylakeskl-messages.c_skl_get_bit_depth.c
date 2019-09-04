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
typedef  enum skl_bitdepth { ____Placeholder_skl_bitdepth } skl_bitdepth ;

/* Variables and functions */
 int SKL_DEPTH_16BIT ; 
 int SKL_DEPTH_24BIT ; 
 int SKL_DEPTH_32BIT ; 
 int SKL_DEPTH_8BIT ; 
 int SKL_DEPTH_INVALID ; 

enum skl_bitdepth skl_get_bit_depth(int params)
{
	switch (params) {
	case 8:
		return SKL_DEPTH_8BIT;

	case 16:
		return SKL_DEPTH_16BIT;

	case 24:
		return SKL_DEPTH_24BIT;

	case 32:
		return SKL_DEPTH_32BIT;

	default:
		return SKL_DEPTH_INVALID;

	}
}