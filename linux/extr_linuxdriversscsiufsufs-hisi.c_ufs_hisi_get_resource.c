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
struct ufs_hisi_host {int /*<<< orphan*/  ufs_sys_ctrl; TYPE_1__* hba; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int ufs_hisi_get_resource(struct ufs_hisi_host *host)
{
	struct resource *mem_res;
	struct device *dev = host->hba->dev;
	struct platform_device *pdev = to_platform_device(dev);

	/* get resource of ufs sys ctrl */
	mem_res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	host->ufs_sys_ctrl = devm_ioremap_resource(dev, mem_res);
	if (IS_ERR(host->ufs_sys_ctrl))
		return PTR_ERR(host->ufs_sys_ctrl);

	return 0;
}