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
struct vml_info {unsigned int num_areas; unsigned long vram_start; TYPE_1__* vram; } ;
struct TYPE_2__ {unsigned long phys; unsigned long size; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vmlfb_vram_offset(struct vml_info *vinfo, unsigned long offset)
{
	unsigned long aoffset;
	unsigned i;

	for (i = 0; i < vinfo->num_areas; ++i) {
		aoffset = offset - (vinfo->vram[i].phys - vinfo->vram_start);

		if (aoffset < vinfo->vram[i].size) {
			return 0;
		}
	}

	return -EINVAL;
}