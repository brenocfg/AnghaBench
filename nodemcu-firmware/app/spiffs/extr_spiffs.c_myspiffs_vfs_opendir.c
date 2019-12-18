#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_dir ;
struct TYPE_2__ {int /*<<< orphan*/ * fns; int /*<<< orphan*/  fs_type; } ;
struct myvfs_dir {TYPE_1__ vfs_dir; int /*<<< orphan*/  d; } ;

/* Variables and functions */
 scalar_t__ SPIFFS_opendir (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VFS_FS_SPIFFS ; 
 int /*<<< orphan*/  free (struct myvfs_dir*) ; 
 int /*<<< orphan*/  fs ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  myspiffs_dd_fns ; 

__attribute__((used)) static vfs_dir *myspiffs_vfs_opendir( const char *name ){
  struct myvfs_dir *dd;

  if (dd = (struct myvfs_dir *)malloc( sizeof( struct myvfs_dir ) )) {
    if (SPIFFS_opendir( &fs, name, &(dd->d) )) {
      dd->vfs_dir.fs_type = VFS_FS_SPIFFS;
      dd->vfs_dir.fns     = &myspiffs_dd_fns;
      return (vfs_dir *)dd;
    } else {
      free( dd );
    }
  }

  return NULL;
}