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
struct dsp_segment_desc {int segment_type; } ;
struct dsp_module_desc {int nsegments; struct dsp_segment_desc* segments; } ;

/* Variables and functions */

__attribute__((used)) static struct dsp_segment_desc * get_segment_desc (struct dsp_module_desc * module, int seg_type)
{
	int i;
	for (i = 0;i < module->nsegments; ++i) {
		if (module->segments[i].segment_type == seg_type) {
			return (module->segments + i);
		}
	}

	return NULL;
}