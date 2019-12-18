#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* chdir ) (char*) ;int /*<<< orphan*/  (* chdrive ) (char*) ;} ;
typedef  TYPE_1__ vfs_fs_fns ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int VFS_RES_ERR ; 
 int VFS_RES_OK ; 
 scalar_t__ dir_level ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* myfatfs_realm (char const*,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__* myspiffs_realm (char const*,char**,int /*<<< orphan*/ ) ; 
 char* normalize_path (char const*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int stub2 (char*) ; 
 int stub3 (char*) ; 

int32_t vfs_chdir( const char *path )
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
  while (strlen( level ) > 0) {
    dir_level++;
    if (level = strchr( level, '/' )) {
      level++;
    } else {
      break;
    }
  }
#endif

#ifdef BUILD_SPIFFS
  if (fs_fns = myspiffs_realm( normpath, &outname, TRUE )) {
    // our SPIFFS integration doesn't support directories
    if (strlen( outname ) == 0) {
      ok = VFS_RES_OK;
    }
  }
#endif

#ifdef BUILD_FATFS
  if (fs_fns = myfatfs_realm( normpath, &outname, TRUE )) {
    if (strchr( outname, ':' )) {
      // need to set FatFS' default drive
      fs_fns->chdrive( outname );
      // and force chdir to root in case path points only to root
      fs_fns->chdir( "/" );
    }
    if (fs_fns->chdir( outname ) == VFS_RES_OK) {
      ok = VFS_RES_OK;
    }
    free( outname );
  }
#endif

  return ok == VFS_RES_OK ? VFS_RES_OK : VFS_RES_ERR;
}