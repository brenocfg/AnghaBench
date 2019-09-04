#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_vol ;
struct TYPE_3__ {int /*<<< orphan*/ * fns; int /*<<< orphan*/  fs_type; } ;
struct myvfs_vol {struct myvfs_vol* ldrname; TYPE_1__ vfs_vol; int /*<<< orphan*/  fs; } ;
struct TYPE_4__ {int pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FR_OK ; 
 int NUM_LOGICAL_DRIVES ; 
 int /*<<< orphan*/  VFS_FS_FATFS ; 
 TYPE_2__* VolToPart ; 
 int /*<<< orphan*/  c_free (struct myvfs_vol*) ; 
 struct myvfs_vol* c_malloc (int) ; 
 struct myvfs_vol* c_strdup (char const*) ; 
 size_t c_strlen (char const*) ; 
 scalar_t__ c_strncmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  f_mount (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  last_result ; 
 int /*<<< orphan*/  myfatfs_vol_fns ; 
 char const** volstr ; 

__attribute__((used)) static vfs_vol *myfatfs_mount( const char *name, int num )
{
  struct myvfs_vol *vol;
  const size_t len = c_strlen( name );

  // num argument specifies the physical driver = SS/CS pin number for this sd card
  if (num >= 0) {
    for (int i = 0; i < NUM_LOGICAL_DRIVES; i++) {
      if (0 == c_strncmp( name, volstr[i], c_strlen( volstr[i] ) )) {
        VolToPart[i].pd = num;
      }
    }
  }

  if (vol = c_malloc( sizeof( struct myvfs_vol ) )) {
    if (vol->ldrname = c_strdup( name )) {
      if (FR_OK == (last_result = f_mount( &(vol->fs), name, 1 ))) {
	vol->vfs_vol.fs_type = VFS_FS_FATFS;
	vol->vfs_vol.fns     = &myfatfs_vol_fns;
	return (vfs_vol *)vol;
      }
    }
  }

  if (vol) {
    if (vol->ldrname) c_free( vol->ldrname );
    c_free( vol );
  }
  return NULL;
}