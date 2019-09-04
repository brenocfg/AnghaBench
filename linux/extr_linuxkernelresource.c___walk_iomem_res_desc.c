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
typedef  scalar_t__ u64 ;
struct resource {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_next_iomem_res (struct resource*,unsigned long,int) ; 
 int stub1 (struct resource*,void*) ; 

__attribute__((used)) static int __walk_iomem_res_desc(struct resource *res, unsigned long desc,
				 bool first_level_children_only,
				 void *arg,
				 int (*func)(struct resource *, void *))
{
	u64 orig_end = res->end;
	int ret = -1;

	while ((res->start < res->end) &&
	       !find_next_iomem_res(res, desc, first_level_children_only)) {
		ret = (*func)(res, arg);
		if (ret)
			break;

		res->start = res->end + 1;
		res->end = orig_end;
	}

	return ret;
}