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
struct ocfs2_super {int dummy; } ;
struct ocfs2_space_resv {void* l_len; void* l_start; scalar_t__ l_whence; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
typedef  void* s64 ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 long EOPNOTSUPP ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int OCFS2_IOC_RESVSP64 ; 
 int OCFS2_IOC_UNRESVSP64 ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 long __ocfs2_change_file_space (int /*<<< orphan*/ *,struct inode*,scalar_t__,int,struct ocfs2_space_resv*,int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  ocfs2_writes_unwritten_extents (struct ocfs2_super*) ; 

__attribute__((used)) static long ocfs2_fallocate(struct file *file, int mode, loff_t offset,
			    loff_t len)
{
	struct inode *inode = file_inode(file);
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_space_resv sr;
	int change_size = 1;
	int cmd = OCFS2_IOC_RESVSP64;

	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		return -EOPNOTSUPP;
	if (!ocfs2_writes_unwritten_extents(osb))
		return -EOPNOTSUPP;

	if (mode & FALLOC_FL_KEEP_SIZE)
		change_size = 0;

	if (mode & FALLOC_FL_PUNCH_HOLE)
		cmd = OCFS2_IOC_UNRESVSP64;

	sr.l_whence = 0;
	sr.l_start = (s64)offset;
	sr.l_len = (s64)len;

	return __ocfs2_change_file_space(NULL, inode, offset, cmd, &sr,
					 change_size);
}