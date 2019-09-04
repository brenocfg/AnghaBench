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
struct scsi_dev_info_list {int /*<<< orphan*/  dev_info_list; } ;
typedef  enum scsi_devinfo_key { ____Placeholder_scsi_devinfo_key } scsi_devinfo_key ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct scsi_dev_info_list*) ; 
 int PTR_ERR (struct scsi_dev_info_list*) ; 
 int /*<<< orphan*/  kfree (struct scsi_dev_info_list*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct scsi_dev_info_list* scsi_dev_info_list_find (char*,char*,int) ; 

int scsi_dev_info_list_del_keyed(char *vendor, char *model,
				 enum scsi_devinfo_key key)
{
	struct scsi_dev_info_list *found;

	found = scsi_dev_info_list_find(vendor, model, key);
	if (IS_ERR(found))
		return PTR_ERR(found);

	list_del(&found->dev_info_list);
	kfree(found);
	return 0;
}