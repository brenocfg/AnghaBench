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
struct pnfs_layout_hdr {int dummy; } ;
struct TYPE_3__ {struct inode* inode; } ;
struct nfs4_layoutget {TYPE_1__ args; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 TYPE_2__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  nfs_layoutget_end (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_clear_first_layoutget (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_layoutget_free (struct nfs4_layoutget*) ; 

void nfs4_lgopen_release(struct nfs4_layoutget *lgp)
{
	if (lgp != NULL) {
		struct inode *inode = lgp->args.inode;
		if (inode) {
			struct pnfs_layout_hdr *lo = NFS_I(inode)->layout;
			pnfs_clear_first_layoutget(lo);
			nfs_layoutget_end(lo);
		}
		pnfs_layoutget_free(lgp);
	}
}