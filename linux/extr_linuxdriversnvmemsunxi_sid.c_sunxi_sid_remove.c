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
struct platform_device {int dummy; } ;
struct nvmem_device {int dummy; } ;

/* Variables and functions */
 int nvmem_unregister (struct nvmem_device*) ; 
 struct nvmem_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int sunxi_sid_remove(struct platform_device *pdev)
{
	struct nvmem_device *nvmem = platform_get_drvdata(pdev);

	return nvmem_unregister(nvmem);
}