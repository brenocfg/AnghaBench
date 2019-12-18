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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_STALE ; 
 int /*<<< orphan*/  nfs_zap_caches_locked (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_invalidate_inode(struct inode *inode)
{
	set_bit(NFS_INO_STALE, &NFS_I(inode)->flags);
	nfs_zap_caches_locked(inode);
}