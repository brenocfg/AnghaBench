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
struct inode {int i_flags; } ;
struct hfsplus_inode_info {int userflags; } ;

/* Variables and functions */
 unsigned int FS_APPEND_FL ; 
 unsigned int FS_IMMUTABLE_FL ; 
 unsigned int FS_NODUMP_FL ; 
 int HFSPLUS_FLG_NODUMP ; 
 struct hfsplus_inode_info* HFSPLUS_I (struct inode*) ; 
 int S_APPEND ; 
 int S_IMMUTABLE ; 

__attribute__((used)) static inline unsigned int hfsplus_getflags(struct inode *inode)
{
	struct hfsplus_inode_info *hip = HFSPLUS_I(inode);
	unsigned int flags = 0;

	if (inode->i_flags & S_IMMUTABLE)
		flags |= FS_IMMUTABLE_FL;
	if (inode->i_flags & S_APPEND)
		flags |= FS_APPEND_FL;
	if (hip->userflags & HFSPLUS_FLG_NODUMP)
		flags |= FS_NODUMP_FL;
	return flags;
}