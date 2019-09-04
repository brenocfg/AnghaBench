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
struct jfs_inode_info {int active_ag; int /*<<< orphan*/  agstart; int /*<<< orphan*/  ixpxd; } ;
struct inode {int i_ino; } ;
struct iag {int /*<<< orphan*/  agstart; int /*<<< orphan*/ * inoext; } ;

/* Variables and functions */
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 int L2INOSPERIAG ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
diInitInode(struct inode *ip, int iagno, int ino, int extno, struct iag * iagp)
{
	struct jfs_inode_info *jfs_ip = JFS_IP(ip);

	ip->i_ino = (iagno << L2INOSPERIAG) + ino;
	jfs_ip->ixpxd = iagp->inoext[extno];
	jfs_ip->agstart = le64_to_cpu(iagp->agstart);
	jfs_ip->active_ag = -1;
}