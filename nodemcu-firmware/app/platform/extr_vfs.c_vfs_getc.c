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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,int /*<<< orphan*/ ) ; 
 int VFS_EOF ; 
 int /*<<< orphan*/  vfs_eof (int) ; 
 int /*<<< orphan*/  vfs_ferrno (int) ; 
 int vfs_read (int,unsigned char*,int) ; 

int vfs_getc( int fd )
{
  unsigned char c = 0xFF;
  int32_t res;

  if(!vfs_eof( fd )) {
    if (1 != vfs_read( fd, &c, 1 )) {
      NODE_DBG("getc errno %i\n", vfs_ferrno( fd ));
      return VFS_EOF;
    } else {
      return (int)c;
    }
  }
  return VFS_EOF;
}