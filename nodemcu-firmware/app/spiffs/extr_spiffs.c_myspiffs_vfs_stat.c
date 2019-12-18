#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfs_stat {char* name; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ spiffs_stat ;
typedef  int /*<<< orphan*/  sint32_t ;

/* Variables and functions */
 int FS_OBJ_NAME_LEN ; 
 scalar_t__ SPIFFS_stat (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  VFS_RES_ERR ; 
 int /*<<< orphan*/  VFS_RES_OK ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  memset (struct vfs_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static sint32_t myspiffs_vfs_stat( const char *name, struct vfs_stat *buf ) {
  spiffs_stat stat;

  if (0 <= SPIFFS_stat( &fs, name, &stat )) {
    memset( buf, 0, sizeof( struct vfs_stat ) );

    // fill in supported stat entries
    strncpy( buf->name, stat.name, FS_OBJ_NAME_LEN+1 );
    buf->name[FS_OBJ_NAME_LEN] = '\0';
    buf->size = stat.size;

    return VFS_RES_OK;
  } else {
    return VFS_RES_ERR;
  }
}