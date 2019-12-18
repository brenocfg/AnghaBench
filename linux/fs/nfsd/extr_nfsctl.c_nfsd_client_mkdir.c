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
typedef  int u32 ;
struct tree_descr {int dummy; } ;
struct nfsdfs_client {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  nfsd_client_dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  nfsd_client_rmdir (struct dentry*) ; 
 struct dentry* nfsd_mkdir (int /*<<< orphan*/ ,struct nfsdfs_client*,char*) ; 
 int nfsdfs_create_files (struct dentry*,struct tree_descr const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

struct dentry *nfsd_client_mkdir(struct nfsd_net *nn,
		struct nfsdfs_client *ncl, u32 id,
		const struct tree_descr *files)
{
	struct dentry *dentry;
	char name[11];
	int ret;

	sprintf(name, "%u", id);

	dentry = nfsd_mkdir(nn->nfsd_client_dir, ncl, name);
	if (IS_ERR(dentry)) /* XXX: tossing errors? */
		return NULL;
	ret = nfsdfs_create_files(dentry, files);
	if (ret) {
		nfsd_client_rmdir(dentry);
		return NULL;
	}
	return dentry;
}