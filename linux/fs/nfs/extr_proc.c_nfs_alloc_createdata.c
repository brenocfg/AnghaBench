#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * fattr; TYPE_3__* fh; } ;
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_6__ {struct iattr* sattr; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  fh; } ;
struct nfs_createdata {int /*<<< orphan*/  fattr; TYPE_4__ res; TYPE_3__ fhandle; TYPE_2__ arg; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_createdata* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_createdata *nfs_alloc_createdata(struct inode *dir,
		struct dentry *dentry, struct iattr *sattr)
{
	struct nfs_createdata *data;

	data = kmalloc(sizeof(*data), GFP_KERNEL);

	if (data != NULL) {
		data->arg.fh = NFS_FH(dir);
		data->arg.name = dentry->d_name.name;
		data->arg.len = dentry->d_name.len;
		data->arg.sattr = sattr;
		nfs_fattr_init(&data->fattr);
		data->fhandle.size = 0;
		data->res.fh = &data->fhandle;
		data->res.fattr = &data->fattr;
	}
	return data;
}