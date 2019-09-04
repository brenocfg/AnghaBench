#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_fs_fns ;
struct TYPE_5__ {TYPE_1__* fns; } ;
typedef  TYPE_2__ vfs_file ;
typedef  int /*<<< orphan*/  sint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* ferrno ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

sint32_t vfs_ferrno( int fd )
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
      sint32_t r = fs_fns->ferrno( );
      c_free( outname );
      return r;
    }
#endif
  }
}