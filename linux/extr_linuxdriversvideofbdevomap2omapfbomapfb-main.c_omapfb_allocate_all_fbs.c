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
typedef  int /*<<< orphan*/  vram_sizes ;
typedef  int /*<<< orphan*/  vram_paddrs ;
struct omapfb_info {struct omapfb2_mem_region* region; } ;
struct omapfb2_mem_region {int /*<<< orphan*/  size; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; } ;
struct omapfb2_device {int num_fbs; int /*<<< orphan*/ * fbs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omapfb_info* FB2OFB (int /*<<< orphan*/ ) ; 
 scalar_t__ def_vram ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (unsigned long**,int /*<<< orphan*/ ,int) ; 
 int omapfb_alloc_fbmem_display (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ omapfb_parse_vram_param (scalar_t__,int,unsigned long*,unsigned long*) ; 

__attribute__((used)) static int omapfb_allocate_all_fbs(struct omapfb2_device *fbdev)
{
	int i, r;
	unsigned long vram_sizes[10];
	unsigned long vram_paddrs[10];

	memset(&vram_sizes, 0, sizeof(vram_sizes));
	memset(&vram_paddrs, 0, sizeof(vram_paddrs));

	if (def_vram &&	omapfb_parse_vram_param(def_vram, 10,
				vram_sizes, vram_paddrs)) {
		dev_err(fbdev->dev, "failed to parse vram parameter\n");

		memset(&vram_sizes, 0, sizeof(vram_sizes));
		memset(&vram_paddrs, 0, sizeof(vram_paddrs));
	}

	for (i = 0; i < fbdev->num_fbs; i++) {
		/* allocate memory automatically only for fb0, or if
		 * excplicitly defined with vram or plat data option */
		if (i == 0 || vram_sizes[i] != 0) {
			r = omapfb_alloc_fbmem_display(fbdev->fbs[i],
					vram_sizes[i], vram_paddrs[i]);

			if (r)
				return r;
		}
	}

	for (i = 0; i < fbdev->num_fbs; i++) {
		struct omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);
		struct omapfb2_mem_region *rg;
		rg = ofbi->region;

		DBG("region%d phys %08x virt %p size=%lu\n",
				i,
				rg->paddr,
				rg->vaddr,
				rg->size);
	}

	return 0;
}