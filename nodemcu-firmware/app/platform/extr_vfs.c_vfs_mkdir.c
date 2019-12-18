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
struct TYPE_3__ {int /*<<< orphan*/  (* mkdir ) (char*) ;} ;
typedef  TYPE_1__ vfs_fs_fns ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  VFS_RES_ERR ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* myfatfs_realm (char const*,char**,int /*<<< orphan*/ ) ; 
 char* normalize_path (char const*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

int32_t vfs_mkdir( const char *name )
{
  vfs_fs_fns *fs_fns;
  const char *normname = normalize_path( name );
  char *outname;

#ifdef BUILD_SPIFFS
  // not supported
#endif

#ifdef BUILD_FATFS
  if (fs_fns = myfatfs_realm( normname, &outname, FALSE )) {
    int32_t r = fs_fns->mkdir( outname );
    free( outname );
    return r;
  }
#endif

  return VFS_RES_ERR;
}