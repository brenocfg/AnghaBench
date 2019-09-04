#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct wm_adsp_fw_caps {int num_regions; TYPE_1__* region_defs; } ;
struct wm_adsp_compr_buf {TYPE_3__* dsp; struct wm_adsp_buffer_region* regions; } ;
struct wm_adsp_buffer_region {void* base_addr; void* cumulative_size; void* offset; int /*<<< orphan*/  mem_type; } ;
struct TYPE_6__ {size_t fw; } ;
struct TYPE_5__ {struct wm_adsp_fw_caps* caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  size_offset; int /*<<< orphan*/  base_offset; int /*<<< orphan*/  mem_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  adsp_dbg (TYPE_3__*,char*,int,int /*<<< orphan*/ ,void*,void*,void*) ; 
 int wm_adsp_buffer_read (struct wm_adsp_compr_buf*,int /*<<< orphan*/ ,void**) ; 
 TYPE_2__* wm_adsp_fw ; 

__attribute__((used)) static int wm_adsp_buffer_populate(struct wm_adsp_compr_buf *buf)
{
	const struct wm_adsp_fw_caps *caps = wm_adsp_fw[buf->dsp->fw].caps;
	struct wm_adsp_buffer_region *region;
	u32 offset = 0;
	int i, ret;

	for (i = 0; i < caps->num_regions; ++i) {
		region = &buf->regions[i];

		region->offset = offset;
		region->mem_type = caps->region_defs[i].mem_type;

		ret = wm_adsp_buffer_read(buf, caps->region_defs[i].base_offset,
					  &region->base_addr);
		if (ret < 0)
			return ret;

		ret = wm_adsp_buffer_read(buf, caps->region_defs[i].size_offset,
					  &offset);
		if (ret < 0)
			return ret;

		region->cumulative_size = offset;

		adsp_dbg(buf->dsp,
			 "region=%d type=%d base=%04x off=%04x size=%04x\n",
			 i, region->mem_type, region->base_addr,
			 region->offset, region->cumulative_size);
	}

	return 0;
}