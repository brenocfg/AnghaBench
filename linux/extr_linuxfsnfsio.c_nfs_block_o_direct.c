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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_INO_ODIRECT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_block_o_direct(struct nfs_inode *nfsi, struct inode *inode)
{
	if (test_bit(NFS_INO_ODIRECT, &nfsi->flags)) {
		clear_bit(NFS_INO_ODIRECT, &nfsi->flags);
		inode_dio_wait(inode);
	}
}