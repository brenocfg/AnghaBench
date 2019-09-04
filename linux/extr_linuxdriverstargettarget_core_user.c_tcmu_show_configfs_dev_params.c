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
struct tcmu_dev {char* dev_config; int dev_size; int /*<<< orphan*/  max_blocks; } ;
struct se_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int TCMU_BLOCKS_TO_MBS (int /*<<< orphan*/ ) ; 
 struct tcmu_dev* TCMU_DEV (struct se_device*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t tcmu_show_configfs_dev_params(struct se_device *dev, char *b)
{
	struct tcmu_dev *udev = TCMU_DEV(dev);
	ssize_t bl = 0;

	bl = sprintf(b + bl, "Config: %s ",
		     udev->dev_config[0] ? udev->dev_config : "NULL");
	bl += sprintf(b + bl, "Size: %llu ", udev->dev_size);
	bl += sprintf(b + bl, "MaxDataAreaMB: %u\n",
		      TCMU_BLOCKS_TO_MBS(udev->max_blocks));

	return bl;
}