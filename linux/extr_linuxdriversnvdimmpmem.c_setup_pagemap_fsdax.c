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
struct dev_pagemap {int /*<<< orphan*/  page_free; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MEMORY_DEVICE_FS_DAX ; 
 int /*<<< orphan*/  dev_pagemap_get_ops () ; 
 scalar_t__ devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct dev_pagemap*) ; 
 int /*<<< orphan*/  fsdax_pagefree ; 
 int /*<<< orphan*/  pmem_release_pgmap_ops ; 

__attribute__((used)) static int setup_pagemap_fsdax(struct device *dev, struct dev_pagemap *pgmap)
{
	dev_pagemap_get_ops();
	if (devm_add_action_or_reset(dev, pmem_release_pgmap_ops, pgmap))
		return -ENOMEM;
	pgmap->type = MEMORY_DEVICE_FS_DAX;
	pgmap->page_free = fsdax_pagefree;

	return 0;
}