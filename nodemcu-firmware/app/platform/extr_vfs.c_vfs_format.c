#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* format ) () ;} ;
typedef  TYPE_1__ vfs_fs_fns ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* myspiffs_realm (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

int32_t vfs_format( void )
{
  vfs_fs_fns *fs_fns;
  char *outname;

#ifdef BUILD_SPIFFS
  if (fs_fns = myspiffs_realm( "/FLASH", &outname, FALSE )) {
    return fs_fns->format();
  }
#endif

#ifdef BUILD_FATFS
  // not supported
#endif

  // Error
  return 0;
}