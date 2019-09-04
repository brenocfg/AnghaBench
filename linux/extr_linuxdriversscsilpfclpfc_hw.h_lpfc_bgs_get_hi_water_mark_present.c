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
typedef  int uint32_t ;

/* Variables and functions */
 int BGS_HI_WATER_MARK_PRESENT_MASK ; 
 int BGS_HI_WATER_MARK_PRESENT_SHIFT ; 

__attribute__((used)) static inline uint32_t
lpfc_bgs_get_hi_water_mark_present(uint32_t bgstat)
{
	return (bgstat & BGS_HI_WATER_MARK_PRESENT_MASK) >>
				BGS_HI_WATER_MARK_PRESENT_SHIFT;
}