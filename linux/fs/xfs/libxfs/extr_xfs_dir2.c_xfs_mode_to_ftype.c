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

/* Variables and functions */
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 unsigned char XFS_DIR3_FT_BLKDEV ; 
 unsigned char XFS_DIR3_FT_CHRDEV ; 
 unsigned char XFS_DIR3_FT_DIR ; 
 unsigned char XFS_DIR3_FT_FIFO ; 
 unsigned char XFS_DIR3_FT_REG_FILE ; 
 unsigned char XFS_DIR3_FT_SOCK ; 
 unsigned char XFS_DIR3_FT_SYMLINK ; 
 unsigned char XFS_DIR3_FT_UNKNOWN ; 

unsigned char
xfs_mode_to_ftype(
	int		mode)
{
	switch (mode & S_IFMT) {
	case S_IFREG:
		return XFS_DIR3_FT_REG_FILE;
	case S_IFDIR:
		return XFS_DIR3_FT_DIR;
	case S_IFCHR:
		return XFS_DIR3_FT_CHRDEV;
	case S_IFBLK:
		return XFS_DIR3_FT_BLKDEV;
	case S_IFIFO:
		return XFS_DIR3_FT_FIFO;
	case S_IFSOCK:
		return XFS_DIR3_FT_SOCK;
	case S_IFLNK:
		return XFS_DIR3_FT_SYMLINK;
	default:
		return XFS_DIR3_FT_UNKNOWN;
	}
}