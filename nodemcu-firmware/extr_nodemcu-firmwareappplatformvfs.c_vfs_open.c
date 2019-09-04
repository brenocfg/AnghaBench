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

/* Variables and functions */
 char* normalize_path (char const*) ; 

int vfs_open( const char *name, const char *mode )
{
  vfs_fs_fns *fs_fns;
  const char *normname = normalize_path( name );
  char *outname;

#ifdef BUILD_SPIFFS
  if (fs_fns = myspiffs_realm( normname, &outname, FALSE )) {
    return (int)fs_fns->open( outname, mode );
  }
#endif

#ifdef BUILD_FATFS
  if (fs_fns = myfatfs_realm( normname, &outname, FALSE )) {
    int r = (int)fs_fns->open( outname, mode );
    c_free( outname );
    return r;
  }
#endif

  return 0;
}