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
struct omapfb_info {int id; struct omapfb2_device* fbdev; } ;
struct omapfb2_mem_region {int dummy; } ;
struct omapfb2_device {int num_fbs; struct omapfb2_mem_region* regions; } ;

/* Variables and functions */
 int OMAPFB_MEM_IDX_ENABLED ; 
 int OMAPFB_MEM_IDX_MASK ; 

__attribute__((used)) static struct omapfb2_mem_region *get_mem_region(struct omapfb_info *ofbi,
						 u8 mem_idx)
{
	struct omapfb2_device *fbdev = ofbi->fbdev;

	if (mem_idx & OMAPFB_MEM_IDX_ENABLED)
		mem_idx &= OMAPFB_MEM_IDX_MASK;
	else
		mem_idx = ofbi->id;

	if (mem_idx >= fbdev->num_fbs)
		return NULL;

	return &fbdev->regions[mem_idx];
}