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
struct uio_pdrv_genirq_platdata {TYPE_1__* pdev; } ;
struct uio_info {struct uio_pdrv_genirq_platdata* priv; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uio_pdrv_genirq_release(struct uio_info *info, struct inode *inode)
{
	struct uio_pdrv_genirq_platdata *priv = info->priv;

	/* Tell the Runtime PM code that the device has become idle */
	pm_runtime_put_sync(&priv->pdev->dev);
	return 0;
}