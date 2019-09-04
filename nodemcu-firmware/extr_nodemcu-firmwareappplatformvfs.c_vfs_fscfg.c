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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_RES_ERR ; 

sint32_t vfs_fscfg( const char *name, uint32_t *phys_addr, uint32_t *phys_size)
{
  vfs_fs_fns *fs_fns;
  char *outname;

#ifdef BUILD_SPIFFS
  if (fs_fns = myspiffs_realm( "/FLASH", &outname, FALSE )) {
    return fs_fns->fscfg( phys_addr, phys_size );
  }
#endif

#ifdef BUILD_FATFS
  // not supported
#endif

  // Error
  return VFS_RES_ERR;
}