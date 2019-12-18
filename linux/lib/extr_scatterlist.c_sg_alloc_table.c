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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SG_MAX_SINGLE_ALLOC ; 
 int __sg_alloc_table (struct sg_table*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sg_free_table (struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_kfree ; 
 int /*<<< orphan*/  sg_kmalloc ; 
 scalar_t__ unlikely (int) ; 

int sg_alloc_table(struct sg_table *table, unsigned int nents, gfp_t gfp_mask)
{
	int ret;

	ret = __sg_alloc_table(table, nents, SG_MAX_SINGLE_ALLOC,
			       NULL, 0, gfp_mask, sg_kmalloc);
	if (unlikely(ret))
		__sg_free_table(table, SG_MAX_SINGLE_ALLOC, 0, sg_kfree);

	return ret;
}