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
struct inode {int /*<<< orphan*/  i_cdev; } ;
struct fw_mgmt {int dummy; } ;
struct file {struct fw_mgmt* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 struct fw_mgmt* get_fw_mgmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fw_mgmt_open(struct inode *inode, struct file *file)
{
	struct fw_mgmt *fw_mgmt = get_fw_mgmt(inode->i_cdev);

	/* fw_mgmt structure can't get freed until file descriptor is closed */
	if (fw_mgmt) {
		file->private_data = fw_mgmt;
		return 0;
	}

	return -ENODEV;
}