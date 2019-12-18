#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* ferrno ) () ;} ;
typedef  TYPE_2__ vfs_fs_fns ;
struct TYPE_9__ {TYPE_1__* fns; } ;
typedef  TYPE_3__ vfs_file ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* ferrno ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* myfatfs_realm (char const*,char**,int /*<<< orphan*/ ) ; 
 TYPE_2__* myspiffs_realm (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 

int32_t vfs_ferrno( int fd )
{
  vfs_file *f = (vfs_file *)fd;

  if (f) {
    return f->fns->ferrno ? f->fns->ferrno( f ) : 0;
  } else {
    vfs_fs_fns *fs_fns;
    const char *name = "";  // current drive
    char *outname;

#ifdef BUILD_SPIFFS
    if (fs_fns = myspiffs_realm( name, &outname, FALSE )) {
      return fs_fns->ferrno( );
    }
#endif

#ifdef BUILD_FATFS
    if (fs_fns = myfatfs_realm( name, &outname, FALSE )) {
      int32_t r = fs_fns->ferrno( );
      free( outname );
      return r;
    }
#endif
  }
}