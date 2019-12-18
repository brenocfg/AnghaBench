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
 int /*<<< orphan*/  devm_memremap_pages_release ; 
 int /*<<< orphan*/  devm_release_action (struct device*,int /*<<< orphan*/ ,struct dev_pagemap*) ; 

void devm_memunmap_pages(struct device *dev, struct dev_pagemap *pgmap)
{
	devm_release_action(dev, devm_memremap_pages_release, pgmap);
}