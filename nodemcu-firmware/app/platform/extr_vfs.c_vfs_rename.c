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
struct TYPE_4__ {int (* rename ) (char*,char*) ;} ;
typedef  TYPE_1__ vfs_fs_fns ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* myfatfs_realm (char const*,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__* myspiffs_realm (char const*,char**,int /*<<< orphan*/ ) ; 
 char* normalize_path (char const*) ; 
 int stub1 (char*,char*) ; 
 int stub2 (char*,char*) ; 

int32_t vfs_rename( const char *oldname, const char *newname )
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
      int32_t r = fs_fns->rename( oldoutname, newoutname );
      free( oldoutname );
      free( newoutname );
      return r;
    }
    free( oldoutname );
  }
#endif

  return -1;
}