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
typedef  int /*<<< orphan*/  vfs_fs_fns ;
typedef  int sint32_t ;

/* Variables and functions */
 int VFS_RES_ERR ; 
 int VFS_RES_OK ; 
 char* normalize_path (char const*) ; 

sint32_t vfs_chdir( const char *path )
{
  vfs_fs_fns *fs_fns;
  const char *normpath = normalize_path( path );
  const char *level;
  char *outname;
  int ok = VFS_RES_ERR;

#if LDRV_TRAVERSAL
  // track dir level
  if (normpath[0] == '/') {
    dir_level = 0;
    level = &(normpath[1]);
  } else {
    level = normpath;
  }
  while (c_strlen( level ) > 0) {
    dir_level++;
    if (level = c_strchr( level, '/' )) {
      level++;
    } else {
      break;
    }
  }
#endif

#ifdef BUILD_SPIFFS
  if (fs_fns = myspiffs_realm( normpath, &outname, TRUE )) {
    // our SPIFFS integration doesn't support directories
    if (c_strlen( outname ) == 0) {
      ok = VFS_RES_OK;
    }
  }
#endif

#ifdef BUILD_FATFS
  if (fs_fns = myfatfs_realm( normpath, &outname, TRUE )) {
    if (c_strchr( outname, ':' )) {
      // need to set FatFS' default drive
      fs_fns->chdrive( outname );
      // and force chdir to root in case path points only to root
      fs_fns->chdir( "/" );
    }
    if (fs_fns->chdir( outname ) == VFS_RES_OK) {
      ok = VFS_RES_OK;
    }
    c_free( outname );
  }
#endif

  return ok == VFS_RES_OK ? VFS_RES_OK : VFS_RES_ERR;
}