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
typedef  int /*<<< orphan*/  vfs_file ;
struct TYPE_2__ {int /*<<< orphan*/ * fns; int /*<<< orphan*/  fs_type; } ;
struct myvfs_file {TYPE_1__ vfs_file; int /*<<< orphan*/  fp; } ;
typedef  int BYTE ;

/* Variables and functions */
 int const FA_OPEN_ALWAYS ; 
 int /*<<< orphan*/  FR_OK ; 
 int /*<<< orphan*/  VFS_FS_FATFS ; 
 int /*<<< orphan*/  f_lseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_open (int /*<<< orphan*/ *,char const*,int const) ; 
 int /*<<< orphan*/  f_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct myvfs_file*) ; 
 int /*<<< orphan*/  last_result ; 
 struct myvfs_file* malloc (int) ; 
 int /*<<< orphan*/  myfatfs_file_fns ; 
 int myfatfs_mode2flag (char const*) ; 

__attribute__((used)) static vfs_file *myfatfs_open( const char *name, const char *mode )
{
  struct myvfs_file *fd;
  const BYTE flags = myfatfs_mode2flag( mode );

  if (fd = malloc( sizeof( struct myvfs_file ) )) {
    if (FR_OK == (last_result = f_open( &(fd->fp), name, flags ))) {
      // skip to end of file for append mode
      if (flags & FA_OPEN_ALWAYS)
        f_lseek( &(fd->fp), f_size( &(fd->fp) ) );

      fd->vfs_file.fs_type = VFS_FS_FATFS;
      fd->vfs_file.fns     = &myfatfs_file_fns;
      return (vfs_file *)fd;
    } else {
      free( fd );
    }
  }

  return NULL;
}