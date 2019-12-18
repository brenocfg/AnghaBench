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
struct resource {scalar_t__ start; scalar_t__ end; unsigned long flags; unsigned long desc; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_2__ {struct resource* child; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 unsigned long IORES_DESC_NONE ; 
 TYPE_1__ iomem_resource ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct resource* next_resource (struct resource*,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_lock ; 

__attribute__((used)) static int find_next_iomem_res(resource_size_t start, resource_size_t end,
			       unsigned long flags, unsigned long desc,
			       bool first_lvl, struct resource *res)
{
	bool siblings_only = true;
	struct resource *p;

	if (!res)
		return -EINVAL;

	if (start >= end)
		return -EINVAL;

	read_lock(&resource_lock);

	for (p = iomem_resource.child; p; p = next_resource(p, siblings_only)) {
		/* If we passed the resource we are looking for, stop */
		if (p->start > end) {
			p = NULL;
			break;
		}

		/* Skip until we find a range that matches what we look for */
		if (p->end < start)
			continue;

		/*
		 * Now that we found a range that matches what we look for,
		 * check the flags and the descriptor. If we were not asked to
		 * use only the first level, start looking at children as well.
		 */
		siblings_only = first_lvl;

		if ((p->flags & flags) != flags)
			continue;
		if ((desc != IORES_DESC_NONE) && (desc != p->desc))
			continue;

		/* Found a match, break */
		break;
	}

	if (p) {
		/* copy data */
		res->start = max(start, p->start);
		res->end = min(end, p->end);
		res->flags = p->flags;
		res->desc = p->desc;
	}

	read_unlock(&resource_lock);
	return p ? 0 : -ENODEV;
}