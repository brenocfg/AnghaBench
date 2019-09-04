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
struct resource {int /*<<< orphan*/  start; } ;
struct nd_namespace_io {int /*<<< orphan*/  bb; int /*<<< orphan*/  addr; struct resource res; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_exit_badblocks (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_memunmap (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_release_mem_region (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

void devm_nsio_disable(struct device *dev, struct nd_namespace_io *nsio)
{
	struct resource *res = &nsio->res;

	devm_memunmap(dev, nsio->addr);
	devm_exit_badblocks(dev, &nsio->bb);
	devm_release_mem_region(dev, res->start, resource_size(res));
}