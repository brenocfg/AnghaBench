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
struct scatterlist {unsigned int offset; } ;
struct cxgbi_task_tag_info {int /*<<< orphan*/  hdr; } ;
struct cxgbi_pagepod_hdr {int dummy; } ;
struct cxgbi_pagepod {unsigned long long* addr; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int PPOD_PAGES_MAX ; 
 unsigned long long cpu_to_be64 (unsigned long) ; 
 int /*<<< orphan*/  memcpy (struct cxgbi_pagepod*,int /*<<< orphan*/ *,int) ; 
 unsigned long sg_dma_address (struct scatterlist*) ; 
 unsigned int sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static void
cxgbit_set_one_ppod(struct cxgbi_pagepod *ppod,
		    struct cxgbi_task_tag_info *ttinfo,
		    struct scatterlist **sg_pp, unsigned int *sg_off)
{
	struct scatterlist *sg = sg_pp ? *sg_pp : NULL;
	unsigned int offset = sg_off ? *sg_off : 0;
	dma_addr_t addr = 0UL;
	unsigned int len = 0;
	int i;

	memcpy(ppod, &ttinfo->hdr, sizeof(struct cxgbi_pagepod_hdr));

	if (sg) {
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);
	}

	for (i = 0; i < PPOD_PAGES_MAX; i++) {
		if (sg) {
			ppod->addr[i] = cpu_to_be64(addr + offset);
			offset += PAGE_SIZE;
			if (offset == (len + sg->offset)) {
				offset = 0;
				sg = sg_next(sg);
				if (sg) {
					addr = sg_dma_address(sg);
					len = sg_dma_len(sg);
				}
			}
		} else {
			ppod->addr[i] = 0ULL;
		}
	}

	/*
	 * the fifth address needs to be repeated in the next ppod, so do
	 * not move sg
	 */
	if (sg_pp) {
		*sg_pp = sg;
		*sg_off = offset;
	}

	if (offset == len) {
		offset = 0;
		if (sg) {
			sg = sg_next(sg);
			if (sg)
				addr = sg_dma_address(sg);
		}
	}
	ppod->addr[i] = sg ? cpu_to_be64(addr + offset) : 0ULL;
}