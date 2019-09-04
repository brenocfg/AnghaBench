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
struct resource {scalar_t__ start; scalar_t__ end; int flags; unsigned long desc; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_2__ {struct resource* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long IORES_DESC_NONE ; 
 TYPE_1__ iomem_resource ; 
 struct resource* next_resource (struct resource*,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_lock ; 

__attribute__((used)) static int find_next_iomem_res(struct resource *res, unsigned long desc,
			       bool first_level_children_only)
{
	resource_size_t start, end;
	struct resource *p;
	bool sibling_only = false;

	BUG_ON(!res);

	start = res->start;
	end = res->end;
	BUG_ON(start >= end);

	if (first_level_children_only)
		sibling_only = true;

	read_lock(&resource_lock);

	for (p = iomem_resource.child; p; p = next_resource(p, sibling_only)) {
		if ((p->flags & res->flags) != res->flags)
			continue;
		if ((desc != IORES_DESC_NONE) && (desc != p->desc))
			continue;
		if (p->start > end) {
			p = NULL;
			break;
		}
		if ((p->end >= start) && (p->start < end))
			break;
	}

	read_unlock(&resource_lock);
	if (!p)
		return -1;
	/* copy data */
	if (res->start < p->start)
		res->start = p->start;
	if (res->end > p->end)
		res->end = p->end;
	res->flags = p->flags;
	res->desc = p->desc;
	return 0;
}