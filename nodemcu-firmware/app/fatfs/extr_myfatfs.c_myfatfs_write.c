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
struct vfs_file {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  GET_FIL_FP (struct vfs_file const*) ; 
 int /*<<< orphan*/  VFS_RES_ERR ; 
 scalar_t__ f_write (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fp ; 
 scalar_t__ last_result ; 

__attribute__((used)) static int32_t myfatfs_write( const struct vfs_file *fd, const void *ptr, size_t len )
{
  GET_FIL_FP(fd);
  UINT act_written;

  last_result = f_write( fp, ptr, len, &act_written );

  return last_result == FR_OK ? act_written : VFS_RES_ERR;
}