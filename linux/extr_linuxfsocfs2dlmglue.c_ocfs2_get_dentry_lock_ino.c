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
struct ocfs2_lock_res {int /*<<< orphan*/ * l_name; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 size_t OCFS2_DENTRY_LOCK_INO_START ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __u64 ocfs2_get_dentry_lock_ino(struct ocfs2_lock_res *lockres)
{
	__be64 inode_blkno_be;

	memcpy(&inode_blkno_be, &lockres->l_name[OCFS2_DENTRY_LOCK_INO_START],
	       sizeof(__be64));

	return be64_to_cpu(inode_blkno_be);
}