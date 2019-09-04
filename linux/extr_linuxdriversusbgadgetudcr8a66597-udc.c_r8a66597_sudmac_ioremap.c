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
struct resource {int dummy; } ;
struct r8a66597 {int /*<<< orphan*/  sudmac_reg; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int r8a66597_sudmac_ioremap(struct r8a66597 *r8a66597,
					  struct platform_device *pdev)
{
	struct resource *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "sudmac");
	r8a66597->sudmac_reg = devm_ioremap_resource(&pdev->dev, res);
	return PTR_ERR_OR_ZERO(r8a66597->sudmac_reg);
}