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
struct sg_table {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCATTERLIST_MAX_SEGMENT ; 
 int __sg_alloc_table_from_pages (struct sg_table*,struct page**,unsigned int,unsigned int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sg_alloc_table_from_pages(struct sg_table *sgt, struct page **pages,
			      unsigned int n_pages, unsigned int offset,
			      unsigned long size, gfp_t gfp_mask)
{
	return __sg_alloc_table_from_pages(sgt, pages, n_pages, offset, size,
					   SCATTERLIST_MAX_SEGMENT, gfp_mask);
}