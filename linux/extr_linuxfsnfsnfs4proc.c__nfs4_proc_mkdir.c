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
struct nfs4_label {int dummy; } ;
struct TYPE_2__ {struct nfs4_label* label; } ;
struct nfs4_createdata {TYPE_1__ arg; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NF4DIR ; 
 struct nfs4_createdata* nfs4_alloc_createdata (struct inode*,int /*<<< orphan*/ *,struct iattr*,int /*<<< orphan*/ ) ; 
 int nfs4_do_create (struct inode*,struct dentry*,struct nfs4_createdata*) ; 
 int /*<<< orphan*/  nfs4_free_createdata (struct nfs4_createdata*) ; 

__attribute__((used)) static int _nfs4_proc_mkdir(struct inode *dir, struct dentry *dentry,
		struct iattr *sattr, struct nfs4_label *label)
{
	struct nfs4_createdata *data;
	int status = -ENOMEM;

	data = nfs4_alloc_createdata(dir, &dentry->d_name, sattr, NF4DIR);
	if (data == NULL)
		goto out;

	data->arg.label = label;
	status = nfs4_do_create(dir, dentry, data);

	nfs4_free_createdata(data);
out:
	return status;
}