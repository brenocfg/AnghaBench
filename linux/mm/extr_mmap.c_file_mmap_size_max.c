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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int FMODE_UNSIGNED_OFFSET ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULONG_MAX ; 

__attribute__((used)) static inline u64 file_mmap_size_max(struct file *file, struct inode *inode)
{
	if (S_ISREG(inode->i_mode))
		return MAX_LFS_FILESIZE;

	if (S_ISBLK(inode->i_mode))
		return MAX_LFS_FILESIZE;

	if (S_ISSOCK(inode->i_mode))
		return MAX_LFS_FILESIZE;

	/* Special "we do even unsigned file positions" case */
	if (file->f_mode & FMODE_UNSIGNED_OFFSET)
		return 0;

	/* Yes, random drivers might want more. But I'm tired of buggy drivers */
	return ULONG_MAX;
}