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
typedef  scalar_t__ sint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FILE_FH (struct vfs_file const*) ; 
 scalar_t__ SPIFFS_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t) ; 
 scalar_t__ VFS_RES_ERR ; 
 int /*<<< orphan*/  fh ; 
 int /*<<< orphan*/  fs ; 

__attribute__((used)) static sint32_t myspiffs_vfs_read( const struct vfs_file *fd, void *ptr, size_t len ) {
  GET_FILE_FH(fd);

  sint32_t n = SPIFFS_read( &fs, fh, ptr, len );

  return n >= 0 ? n : VFS_RES_ERR;
}