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
 int /*<<< orphan*/  VFS_SEEK_CUR ; 
 int vfs_lseek (int,int,int /*<<< orphan*/ ) ; 

int vfs_ungetc( int c, int fd )
{
  return vfs_lseek( fd, -1, VFS_SEEK_CUR );
}