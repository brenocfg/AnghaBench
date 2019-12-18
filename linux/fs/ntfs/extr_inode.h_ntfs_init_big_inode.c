#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  mft_no; } ;
typedef  TYPE_1__ ntfs_inode ;

/* Variables and functions */
 TYPE_1__* NTFS_I (struct inode*) ; 
 int /*<<< orphan*/  __ntfs_init_inode (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 

__attribute__((used)) static inline void ntfs_init_big_inode(struct inode *vi)
{
	ntfs_inode *ni = NTFS_I(vi);

	ntfs_debug("Entering.");
	__ntfs_init_inode(vi->i_sb, ni);
	ni->mft_no = vi->i_ino;
}