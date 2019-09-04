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
typedef  scalar_t__ u32 ;
struct scatterlist {int /*<<< orphan*/  length; } ;
struct rd_dev_sg_table {scalar_t__ page_end_offset; scalar_t__ page_start_offset; scalar_t__ rd_sg_count; struct scatterlist* sg_table; } ;
struct rd_dev {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int RD_MAX_ALLOCATION_SIZE ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scatterlist* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 unsigned char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sg_assign_page (struct scatterlist*,struct page*) ; 
 int /*<<< orphan*/  sg_chain (struct scatterlist*,scalar_t__,struct scatterlist*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,scalar_t__) ; 

__attribute__((used)) static int rd_allocate_sgl_table(struct rd_dev *rd_dev, struct rd_dev_sg_table *sg_table,
				 u32 total_sg_needed, unsigned char init_payload)
{
	u32 i = 0, j, page_offset = 0, sg_per_table;
	u32 max_sg_per_table = (RD_MAX_ALLOCATION_SIZE /
				sizeof(struct scatterlist));
	struct page *pg;
	struct scatterlist *sg;
	unsigned char *p;

	while (total_sg_needed) {
		unsigned int chain_entry = 0;

		sg_per_table = (total_sg_needed > max_sg_per_table) ?
			max_sg_per_table : total_sg_needed;

		/*
		 * Reserve extra element for chain entry
		 */
		if (sg_per_table < total_sg_needed)
			chain_entry = 1;

		sg = kcalloc(sg_per_table + chain_entry, sizeof(*sg),
				GFP_KERNEL);
		if (!sg)
			return -ENOMEM;

		sg_init_table(sg, sg_per_table + chain_entry);

		if (i > 0) {
			sg_chain(sg_table[i - 1].sg_table,
				 max_sg_per_table + 1, sg);
		}

		sg_table[i].sg_table = sg;
		sg_table[i].rd_sg_count = sg_per_table;
		sg_table[i].page_start_offset = page_offset;
		sg_table[i++].page_end_offset = (page_offset + sg_per_table)
						- 1;

		for (j = 0; j < sg_per_table; j++) {
			pg = alloc_pages(GFP_KERNEL, 0);
			if (!pg) {
				pr_err("Unable to allocate scatterlist"
					" pages for struct rd_dev_sg_table\n");
				return -ENOMEM;
			}
			sg_assign_page(&sg[j], pg);
			sg[j].length = PAGE_SIZE;

			p = kmap(pg);
			memset(p, init_payload, PAGE_SIZE);
			kunmap(pg);
		}

		page_offset += sg_per_table;
		total_sg_needed -= sg_per_table;
	}

	return 0;
}