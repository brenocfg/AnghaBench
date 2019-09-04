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
struct qedi_debugfs_ops {int /*<<< orphan*/  name; } ;
struct qedi_dbg_ctx {int host_no; int /*<<< orphan*/  bdf_dentry; } ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_INFO (struct qedi_dbg_ctx*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_DEBUGFS ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct qedi_dbg_ctx*,struct file_operations const*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_dbg_root ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
qedi_dbg_host_init(struct qedi_dbg_ctx *qedi,
		   const struct qedi_debugfs_ops *dops,
		   const struct file_operations *fops)
{
	char host_dirname[32];
	struct dentry *file_dentry = NULL;

	sprintf(host_dirname, "host%u", qedi->host_no);
	qedi->bdf_dentry = debugfs_create_dir(host_dirname, qedi_dbg_root);
	if (!qedi->bdf_dentry)
		return;

	while (dops) {
		if (!(dops->name))
			break;

		file_dentry = debugfs_create_file(dops->name, 0600,
						  qedi->bdf_dentry, qedi,
						  fops);
		if (!file_dentry) {
			QEDI_INFO(qedi, QEDI_LOG_DEBUGFS,
				  "Debugfs entry %s creation failed\n",
				  dops->name);
			debugfs_remove_recursive(qedi->bdf_dentry);
			return;
		}
		dops++;
		fops++;
	}
}