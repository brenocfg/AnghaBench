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
struct platform_device {TYPE_1__* resource; } ;
struct net2272 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct net2272*) ; 
 int /*<<< orphan*/  net2272_remove (struct net2272*) ; 
 struct net2272* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 

__attribute__((used)) static int
net2272_plat_remove(struct platform_device *pdev)
{
	struct net2272 *dev = platform_get_drvdata(pdev);

	net2272_remove(dev);

	release_mem_region(pdev->resource[0].start,
		resource_size(&pdev->resource[0]));

	kfree(dev);

	return 0;
}