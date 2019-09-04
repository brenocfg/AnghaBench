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
struct TYPE_3__ {struct dentry* trc_file; struct dentry* trc_enable; int /*<<< orphan*/  enable; } ;
struct TYPE_4__ {TYPE_1__ trc; int /*<<< orphan*/  trc_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_ERR (char*) ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* snic_glob ; 
 int /*<<< orphan*/  snic_trc_fops ; 

int
snic_trc_debugfs_init(void)
{
	struct dentry *de = NULL;
	int ret = -1;

	if (!snic_glob->trc_root) {
		SNIC_ERR("Debugfs root directory for snic doesn't exist.\n");

		return ret;
	}

	de = debugfs_create_bool("tracing_enable",
				 S_IFREG | S_IRUGO | S_IWUSR,
				 snic_glob->trc_root,
				 &snic_glob->trc.enable);

	if (!de) {
		SNIC_ERR("Can't create trace_enable file.\n");

		return ret;
	}
	snic_glob->trc.trc_enable = de;

	de = debugfs_create_file("trace",
				 S_IFREG | S_IRUGO | S_IWUSR,
				 snic_glob->trc_root,
				 NULL,
				 &snic_trc_fops);

	if (!de) {
		SNIC_ERR("Cannot create trace file.\n");

		return ret;
	}
	snic_glob->trc.trc_file = de;
	ret = 0;

	return ret;
}