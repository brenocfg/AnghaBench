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
struct device {int dummy; } ;
struct dev_pagemap {int dummy; } ;

/* Variables and functions */
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct dev_pagemap*) ; 
 int /*<<< orphan*/  devm_memremap_pages_release ; 
 void* memremap_pages (struct dev_pagemap*,int /*<<< orphan*/ ) ; 

void *devm_memremap_pages(struct device *dev, struct dev_pagemap *pgmap)
{
	int error;
	void *ret;

	ret = memremap_pages(pgmap, dev_to_node(dev));
	if (IS_ERR(ret))
		return ret;

	error = devm_add_action_or_reset(dev, devm_memremap_pages_release,
			pgmap);
	if (error)
		return ERR_PTR(error);
	return ret;
}