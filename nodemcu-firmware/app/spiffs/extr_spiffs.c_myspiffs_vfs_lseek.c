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
 int SPIFFS_SEEK_CUR ; 
 int SPIFFS_SEEK_END ; 
 int SPIFFS_SEEK_SET ; 
 scalar_t__ SPIFFS_lseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ VFS_RES_ERR ; 
#define  VFS_SEEK_CUR 130 
#define  VFS_SEEK_END 129 
#define  VFS_SEEK_SET 128 
 int /*<<< orphan*/  fh ; 
 int /*<<< orphan*/  fs ; 

__attribute__((used)) static sint32_t myspiffs_vfs_lseek( const struct vfs_file *fd, sint32_t off, int whence ) {
  GET_FILE_FH(fd);
  int spiffs_whence;

  switch (whence) {
  default:
  case VFS_SEEK_SET:
    spiffs_whence = SPIFFS_SEEK_SET;
    break;
  case VFS_SEEK_CUR:
    spiffs_whence = SPIFFS_SEEK_CUR;
    break;
  case VFS_SEEK_END:
    spiffs_whence = SPIFFS_SEEK_END;
    break;
  }

  sint32_t res = SPIFFS_lseek( &fs, fh, off, spiffs_whence );
  return res >= 0 ? res : VFS_RES_ERR;
}