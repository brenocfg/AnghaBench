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
struct uio_info {char* name; } ;
struct tcmu_hba {int host_id; } ;
struct tcmu_dev {char* name; char* dev_config; struct uio_info uio_info; TYPE_1__* hba; } ;
struct TYPE_2__ {struct tcmu_hba* hba_ptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int tcmu_update_uio_info(struct tcmu_dev *udev)
{
	struct tcmu_hba *hba = udev->hba->hba_ptr;
	struct uio_info *info;
	size_t size, used;
	char *str;

	info = &udev->uio_info;
	size = snprintf(NULL, 0, "tcm-user/%u/%s/%s", hba->host_id, udev->name,
			udev->dev_config);
	size += 1; /* for \0 */
	str = kmalloc(size, GFP_KERNEL);
	if (!str)
		return -ENOMEM;

	used = snprintf(str, size, "tcm-user/%u/%s", hba->host_id, udev->name);
	if (udev->dev_config[0])
		snprintf(str + used, size - used, "/%s", udev->dev_config);

	/* If the old string exists, free it */
	kfree(info->name);
	info->name = str;

	return 0;
}