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
struct vfs_dir {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  GET_DIR_DP (struct vfs_dir const*) ; 
 int /*<<< orphan*/  VFS_RES_ERR ; 
 int /*<<< orphan*/  VFS_RES_OK ; 
 int /*<<< orphan*/  dp ; 
 scalar_t__ f_closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ last_result ; 

__attribute__((used)) static int32_t myfatfs_closedir( const struct vfs_dir *dd )
{
  GET_DIR_DP(dd);

  last_result = f_closedir( dp );

  // free descriptor memory
  free( (void *)dd );

  return last_result == FR_OK ? VFS_RES_OK : VFS_RES_ERR;
}