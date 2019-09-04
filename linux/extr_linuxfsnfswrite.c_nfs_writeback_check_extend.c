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
typedef  scalar_t__ u64 ;
struct nfs_pgio_res {scalar_t__ count; } ;
struct nfs_pgio_args {scalar_t__ offset; } ;
struct nfs_pgio_header {int /*<<< orphan*/  inode; struct nfs_pgio_res res; struct nfs_pgio_args args; } ;
struct nfs_fattr {int valid; scalar_t__ size; } ;

/* Variables and functions */
 int NFS_ATTR_FATTR_SIZE ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_set_barrier (struct nfs_fattr*) ; 
 scalar_t__ nfs_size_to_loff_t (scalar_t__) ; 

__attribute__((used)) static void nfs_writeback_check_extend(struct nfs_pgio_header *hdr,
		struct nfs_fattr *fattr)
{
	struct nfs_pgio_args *argp = &hdr->args;
	struct nfs_pgio_res *resp = &hdr->res;
	u64 size = argp->offset + resp->count;

	if (!(fattr->valid & NFS_ATTR_FATTR_SIZE))
		fattr->size = size;
	if (nfs_size_to_loff_t(fattr->size) < i_size_read(hdr->inode)) {
		fattr->valid &= ~NFS_ATTR_FATTR_SIZE;
		return;
	}
	if (size != fattr->size)
		return;
	/* Set attribute barrier */
	nfs_fattr_set_barrier(fattr);
	/* ...and update size */
	fattr->valid |= NFS_ATTR_FATTR_SIZE;
}