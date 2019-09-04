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
struct nfsd_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ nfs4_has_reclaimed_state (int /*<<< orphan*/ ,struct nfsd_net*) ; 
 int /*<<< orphan*/  printk (char*,struct dentry*) ; 
 int vfs_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 

__attribute__((used)) static int
purge_old(struct dentry *parent, struct dentry *child, struct nfsd_net *nn)
{
	int status;

	if (nfs4_has_reclaimed_state(child->d_name.name, nn))
		return 0;

	status = vfs_rmdir(d_inode(parent), child);
	if (status)
		printk("failed to remove client recovery directory %pd\n",
				child);
	/* Keep trying, success or failure: */
	return 0;
}