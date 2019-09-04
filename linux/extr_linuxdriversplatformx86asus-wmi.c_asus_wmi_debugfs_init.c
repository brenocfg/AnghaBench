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
struct dentry {int dummy; } ;
struct asus_wmi_debugfs_node {int /*<<< orphan*/  name; struct asus_wmi* asus; } ;
struct TYPE_4__ {int /*<<< orphan*/  root; int /*<<< orphan*/  ctrl_param; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  method_id; } ;
struct asus_wmi {TYPE_2__ debug; TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct asus_wmi_debugfs_node*) ; 
 int ENOMEM ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 struct asus_wmi_debugfs_node* asus_wmi_debug_files ; 
 int /*<<< orphan*/  asus_wmi_debugfs_exit (struct asus_wmi*) ; 
 int /*<<< orphan*/  asus_wmi_debugfs_io_ops ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct asus_wmi_debugfs_node*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_x32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int asus_wmi_debugfs_init(struct asus_wmi *asus)
{
	struct dentry *dent;
	int i;

	asus->debug.root = debugfs_create_dir(asus->driver->name, NULL);
	if (!asus->debug.root) {
		pr_err("failed to create debugfs directory\n");
		goto error_debugfs;
	}

	dent = debugfs_create_x32("method_id", S_IRUGO | S_IWUSR,
				  asus->debug.root, &asus->debug.method_id);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_x32("dev_id", S_IRUGO | S_IWUSR,
				  asus->debug.root, &asus->debug.dev_id);
	if (!dent)
		goto error_debugfs;

	dent = debugfs_create_x32("ctrl_param", S_IRUGO | S_IWUSR,
				  asus->debug.root, &asus->debug.ctrl_param);
	if (!dent)
		goto error_debugfs;

	for (i = 0; i < ARRAY_SIZE(asus_wmi_debug_files); i++) {
		struct asus_wmi_debugfs_node *node = &asus_wmi_debug_files[i];

		node->asus = asus;
		dent = debugfs_create_file(node->name, S_IFREG | S_IRUGO,
					   asus->debug.root, node,
					   &asus_wmi_debugfs_io_ops);
		if (!dent) {
			pr_err("failed to create debug file: %s\n", node->name);
			goto error_debugfs;
		}
	}

	return 0;

error_debugfs:
	asus_wmi_debugfs_exit(asus);
	return -ENOMEM;
}