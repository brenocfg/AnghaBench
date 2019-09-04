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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_flags; } ;
struct nfs_open_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFS_LAYOUT_FIRST_LAYOUTGET ; 
 int /*<<< orphan*/  NFS_LAYOUT_INVALID_STID ; 
 int /*<<< orphan*/  NFS_LAYOUT_RETURN ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  _add_to_server_list (struct pnfs_layout_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_layoutget_begin (struct pnfs_layout_hdr*) ; 
 struct pnfs_layout_hdr* pnfs_find_alloc_layout (struct inode*,struct nfs_open_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ pnfs_layoutgets_blocked (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pnfs_layout_hdr *
_pnfs_grab_empty_layout(struct inode *ino, struct nfs_open_context *ctx)
{
	struct pnfs_layout_hdr *lo;

	spin_lock(&ino->i_lock);
	lo = pnfs_find_alloc_layout(ino, ctx, GFP_KERNEL);
	if (!lo)
		goto out_unlock;
	if (!test_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags))
		goto out_unlock;
	if (test_bit(NFS_LAYOUT_RETURN, &lo->plh_flags))
		goto out_unlock;
	if (pnfs_layoutgets_blocked(lo))
		goto out_unlock;
	if (test_and_set_bit(NFS_LAYOUT_FIRST_LAYOUTGET, &lo->plh_flags))
		goto out_unlock;
	nfs_layoutget_begin(lo);
	spin_unlock(&ino->i_lock);
	_add_to_server_list(lo, NFS_SERVER(ino));
	return lo;

out_unlock:
	spin_unlock(&ino->i_lock);
	pnfs_put_layout_hdr(lo);
	return NULL;
}