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
struct snic {struct dentry* reset_stats_file; struct dentry* stats_host; struct dentry* stats_file; TYPE_1__* shost; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int /*<<< orphan*/  stats_root; } ;
struct TYPE_3__ {int host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_DBG (char*) ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct snic*,int /*<<< orphan*/ *) ; 
 TYPE_2__* snic_glob ; 
 int /*<<< orphan*/  snic_reset_stats_fops ; 
 int /*<<< orphan*/  snic_stats_fops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int
snic_stats_debugfs_init(struct snic *snic)
{
	int rc = -1;
	char name[16];
	struct dentry *de = NULL;

	snprintf(name, sizeof(name), "host%d", snic->shost->host_no);
	if (!snic_glob->stats_root) {
		SNIC_DBG("snic_stats root doesn't exist\n");

		return rc;
	}

	de = debugfs_create_dir(name, snic_glob->stats_root);
	if (!de) {
		SNIC_DBG("Cannot create host directory\n");

		return rc;
	}
	snic->stats_host = de;

	de = debugfs_create_file("stats",
				S_IFREG|S_IRUGO,
				snic->stats_host,
				snic,
				&snic_stats_fops);
	if (!de) {
		SNIC_DBG("Cannot create host's stats file\n");

		return rc;
	}
	snic->stats_file = de;

	de = debugfs_create_file("reset_stats",
				S_IFREG|S_IRUGO|S_IWUSR,
				snic->stats_host,
				snic,
				&snic_reset_stats_fops);

	if (!de) {
		SNIC_DBG("Cannot create host's reset_stats file\n");

		return rc;
	}
	snic->reset_stats_file = de;
	rc = 0;

	return rc;
}