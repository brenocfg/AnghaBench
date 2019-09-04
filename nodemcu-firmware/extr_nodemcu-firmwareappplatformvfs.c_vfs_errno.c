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
typedef  int /*<<< orphan*/  sint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_RES_ERR ; 
 char* normalize_path (char const*) ; 

sint32_t vfs_errno( const char *name )
{
  vfs_fs_fns *fs_fns;
  char *outname;

  if (!name) name = "";  // current drive

  const char *normname = normalize_path( name );

#ifdef BUILD_SPIFFS
  if (fs_fns = myspiffs_realm( normname, &outname, FALSE )) {
    return fs_fns->ferrno( );
  }
#endif

#ifdef BUILD_FATFS
  if (fs_fns = myfatfs_realm( normname, &outname, FALSE )) {
    sint32_t r = fs_fns->ferrno( );
    c_free( outname );
    return r;
  }
#endif

  return VFS_RES_ERR;
}