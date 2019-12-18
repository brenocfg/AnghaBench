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
struct nfs_inode {int /*<<< orphan*/  flags; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_INO_ODIRECT ; 
 int /*<<< orphan*/  nfs_sync_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_block_buffered(struct nfs_inode *nfsi, struct inode *inode)
{
	if (!test_bit(NFS_INO_ODIRECT, &nfsi->flags)) {
		set_bit(NFS_INO_ODIRECT, &nfsi->flags);
		nfs_sync_mapping(inode->i_mapping);
	}
}