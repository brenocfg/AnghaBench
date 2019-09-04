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
struct scsi_dev_info_list_table {char const* name; int key; int /*<<< orphan*/  node; int /*<<< orphan*/  scsi_dev_info_list; } ;
typedef  enum scsi_devinfo_key { ____Placeholder_scsi_devinfo_key } scsi_devinfo_key ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ERR (struct scsi_dev_info_list_table*) ; 
 struct scsi_dev_info_list_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dev_info_list ; 
 struct scsi_dev_info_list_table* scsi_devinfo_lookup_by_key (int) ; 

int scsi_dev_info_add_list(enum scsi_devinfo_key key, const char *name)
{
	struct scsi_dev_info_list_table *devinfo_table =
		scsi_devinfo_lookup_by_key(key);

	if (!IS_ERR(devinfo_table))
		/* list already exists */
		return -EEXIST;

	devinfo_table = kmalloc(sizeof(*devinfo_table), GFP_KERNEL);

	if (!devinfo_table)
		return -ENOMEM;

	INIT_LIST_HEAD(&devinfo_table->node);
	INIT_LIST_HEAD(&devinfo_table->scsi_dev_info_list);
	devinfo_table->name = name;
	devinfo_table->key = key;
	list_add_tail(&devinfo_table->node, &scsi_dev_info_list);

	return 0;
}