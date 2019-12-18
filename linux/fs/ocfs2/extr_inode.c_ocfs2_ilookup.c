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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
struct ocfs2_find_inode_args {scalar_t__ fi_sysfile_type; int /*<<< orphan*/  fi_ino; scalar_t__ fi_flags; int /*<<< orphan*/  fi_blkno; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* ilookup5 (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_find_inode_args*) ; 
 int /*<<< orphan*/  ino_from_blkno (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_find_actor ; 

struct inode *ocfs2_ilookup(struct super_block *sb, u64 blkno)
{
	struct ocfs2_find_inode_args args;

	args.fi_blkno = blkno;
	args.fi_flags = 0;
	args.fi_ino = ino_from_blkno(sb, blkno);
	args.fi_sysfile_type = 0;

	return ilookup5(sb, blkno, ocfs2_find_actor, &args);
}