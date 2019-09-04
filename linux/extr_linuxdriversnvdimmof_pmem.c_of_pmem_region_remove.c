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
struct of_pmem_private {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct of_pmem_private*) ; 
 int /*<<< orphan*/  nvdimm_bus_unregister (int /*<<< orphan*/ ) ; 
 struct of_pmem_private* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int of_pmem_region_remove(struct platform_device *pdev)
{
	struct of_pmem_private *priv = platform_get_drvdata(pdev);

	nvdimm_bus_unregister(priv->bus);
	kfree(priv);

	return 0;
}