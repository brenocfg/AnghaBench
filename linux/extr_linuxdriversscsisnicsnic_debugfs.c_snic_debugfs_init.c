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
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* stats_root; struct dentry* trc_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_DBG (char*) ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 TYPE_1__* snic_glob ; 

int
snic_debugfs_init(void)
{
	int rc = -1;
	struct dentry *de = NULL;

	de = debugfs_create_dir("snic", NULL);
	if (!de) {
		SNIC_DBG("Cannot create debugfs root\n");

		return rc;
	}
	snic_glob->trc_root = de;

	de = debugfs_create_dir("statistics", snic_glob->trc_root);
	if (!de) {
		SNIC_DBG("Cannot create Statistics directory\n");

		return rc;
	}
	snic_glob->stats_root = de;

	rc = 0;

	return rc;
}