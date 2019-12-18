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
struct pnfs_layoutdriver_type {void (* free_layout_hdr ) (struct pnfs_layout_hdr*) ;} ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_lc_cred; int /*<<< orphan*/  plh_layouts; int /*<<< orphan*/  plh_inode; } ;
struct nfs_server {struct nfs_client* nfs_client; struct pnfs_layoutdriver_type* pnfs_curr_ld; } ;
struct nfs_client {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void stub1 (struct pnfs_layout_hdr*) ; 

__attribute__((used)) static void
pnfs_free_layout_hdr(struct pnfs_layout_hdr *lo)
{
	struct nfs_server *server = NFS_SERVER(lo->plh_inode);
	struct pnfs_layoutdriver_type *ld = server->pnfs_curr_ld;

	if (!list_empty(&lo->plh_layouts)) {
		struct nfs_client *clp = server->nfs_client;

		spin_lock(&clp->cl_lock);
		list_del_init(&lo->plh_layouts);
		spin_unlock(&clp->cl_lock);
	}
	put_cred(lo->plh_lc_cred);
	return ld->free_layout_hdr(lo);
}