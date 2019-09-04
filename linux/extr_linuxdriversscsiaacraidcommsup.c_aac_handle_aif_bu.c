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
struct aac_dev {TYPE_1__* pdev; } ;
struct aac_aifcmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AifBuCacheDataLoss 129 
#define  AifBuCacheDataRecover 128 
 int aac_aif_data (struct aac_aifcmd*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void aac_handle_aif_bu(struct aac_dev *dev, struct aac_aifcmd *aifcmd)
{
	switch (aac_aif_data(aifcmd, 1)) {
	case AifBuCacheDataLoss:
		if (aac_aif_data(aifcmd, 2))
			dev_info(&dev->pdev->dev, "Backup unit had cache data loss - [%d]\n",
			aac_aif_data(aifcmd, 2));
		else
			dev_info(&dev->pdev->dev, "Backup Unit had cache data loss\n");
		break;
	case AifBuCacheDataRecover:
		if (aac_aif_data(aifcmd, 2))
			dev_info(&dev->pdev->dev, "DDR cache data recovered successfully - [%d]\n",
			aac_aif_data(aifcmd, 2));
		else
			dev_info(&dev->pdev->dev, "DDR cache data recovered successfully\n");
		break;
	}
}