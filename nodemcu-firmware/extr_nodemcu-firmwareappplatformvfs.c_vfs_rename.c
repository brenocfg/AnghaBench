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
 char* normalize_path (char const*) ; 

sint32_t vfs_rename( const char *oldname, const char *newname )
{
  vfs_fs_fns *fs_fns;
  const char *normoldname = normalize_path( oldname );
  const char *normnewname = normalize_path( newname );
  char *oldoutname, *newoutname;

#ifdef BUILD_SPIFFS
  if (myspiffs_realm( normoldname, &oldoutname, FALSE )) {
    if (fs_fns = myspiffs_realm( normnewname, &newoutname, FALSE )) {
      return fs_fns->rename( oldoutname, newoutname );
    }
  }
#endif

#ifdef BUILD_FATFS
  if (myfatfs_realm( normoldname, &oldoutname, FALSE )) {
    if (fs_fns = myfatfs_realm( normnewname, &newoutname, FALSE )) {
      sint32_t r = fs_fns->rename( oldoutname, newoutname );
      c_free( oldoutname );
      c_free( newoutname );
      return r;
    }
    c_free( oldoutname );
  }
#endif

  return -1;
}