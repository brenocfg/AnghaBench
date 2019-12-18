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
struct vfs_vol {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {void* ldrname; } ;

/* Variables and functions */
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  GET_FATFS_FS (struct vfs_vol const*) ; 
 int /*<<< orphan*/  VFS_RES_ERR ; 
 int /*<<< orphan*/  VFS_RES_OK ; 
 scalar_t__ f_mount (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ last_result ; 
 TYPE_1__* myvol ; 

__attribute__((used)) static int32_t myfatfs_umount( const struct vfs_vol *vol )
{
  GET_FATFS_FS(vol);

  last_result = f_mount( NULL, myvol->ldrname, 0 );

  free( myvol->ldrname );
  free( (void *)vol );

  return last_result == FR_OK ? VFS_RES_OK : VFS_RES_ERR;
}