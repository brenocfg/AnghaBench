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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_flags; struct inode* plh_inode; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  enum pnfs_iomode { ____Placeholder_pnfs_iomode } pnfs_iomode ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_LAYOUT_RETURN_REQUESTED ; 
 scalar_t__ pnfs_layout_need_return (struct pnfs_layout_hdr*) ; 
 int pnfs_prepare_layoutreturn (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pnfs_send_layoutreturn (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pnfs_layoutreturn_before_put_layout_hdr(struct pnfs_layout_hdr *lo)
{
	struct inode *inode= lo->plh_inode;

	if (!test_bit(NFS_LAYOUT_RETURN_REQUESTED, &lo->plh_flags))
		return;
	spin_lock(&inode->i_lock);
	if (pnfs_layout_need_return(lo)) {
		nfs4_stateid stateid;
		enum pnfs_iomode iomode;
		bool send;

		send = pnfs_prepare_layoutreturn(lo, &stateid, &iomode);
		spin_unlock(&inode->i_lock);
		if (send) {
			/* Send an async layoutreturn so we dont deadlock */
			pnfs_send_layoutreturn(lo, &stateid, iomode, false);
		}
	} else
		spin_unlock(&inode->i_lock);
}