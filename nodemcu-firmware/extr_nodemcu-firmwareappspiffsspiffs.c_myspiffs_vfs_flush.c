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
typedef  int /*<<< orphan*/  sint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FILE_FH (struct vfs_file const*) ; 
 scalar_t__ SPIFFS_fflush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS_RES_ERR ; 
 int /*<<< orphan*/  VFS_RES_OK ; 
 int /*<<< orphan*/  fh ; 
 int /*<<< orphan*/  fs ; 

__attribute__((used)) static sint32_t myspiffs_vfs_flush( const struct vfs_file *fd ) {
  GET_FILE_FH(fd);

  return SPIFFS_fflush( &fs, fh ) >= 0 ? VFS_RES_OK : VFS_RES_ERR;
}