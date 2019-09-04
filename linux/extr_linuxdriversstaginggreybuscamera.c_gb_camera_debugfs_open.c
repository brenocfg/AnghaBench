#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct gb_camera_debugfs_entry {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {void* private_data; TYPE_2__ f_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_iname; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct gb_camera_debugfs_entry*) ; 
 struct gb_camera_debugfs_entry* gb_camera_debugfs_entries ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_camera_debugfs_open(struct inode *inode, struct file *file)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(gb_camera_debugfs_entries); ++i) {
		const struct gb_camera_debugfs_entry *entry =
			&gb_camera_debugfs_entries[i];

		if (!strcmp(file->f_path.dentry->d_iname, entry->name)) {
			file->private_data = (void *)entry;
			break;
		}
	}

	return 0;
}