#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int valid; } ;
struct TYPE_8__ {int /*<<< orphan*/  fh; } ;
struct TYPE_6__ {int claim; } ;
struct nfs4_opendata {TYPE_4__ f_attr; int /*<<< orphan*/  dentry; int /*<<< orphan*/  f_label; TYPE_3__ o_res; TYPE_2__* dir; TYPE_1__ o_arg; } ;
struct inode {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  NFS4_OPEN_CLAIM_DELEGATE_CUR 130 
#define  NFS4_OPEN_CLAIM_DELEGATE_PREV 129 
#define  NFS4_OPEN_CLAIM_NULL 128 
 int NFS_ATTR_FATTR ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 struct inode* nfs_fhget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,TYPE_4__*) ; 

__attribute__((used)) static struct inode *
nfs4_opendata_get_inode(struct nfs4_opendata *data)
{
	struct inode *inode;

	switch (data->o_arg.claim) {
	case NFS4_OPEN_CLAIM_NULL:
	case NFS4_OPEN_CLAIM_DELEGATE_CUR:
	case NFS4_OPEN_CLAIM_DELEGATE_PREV:
		if (!(data->f_attr.valid & NFS_ATTR_FATTR))
			return ERR_PTR(-EAGAIN);
		inode = nfs_fhget(data->dir->d_sb, &data->o_res.fh,
				&data->f_attr, data->f_label);
		break;
	default:
		inode = d_inode(data->dentry);
		ihold(inode);
		nfs_refresh_inode(inode, &data->f_attr);
	}
	return inode;
}