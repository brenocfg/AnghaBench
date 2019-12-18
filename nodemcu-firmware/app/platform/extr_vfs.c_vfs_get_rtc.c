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
typedef  int /*<<< orphan*/  vfs_time ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_RES_ERR ; 
 int /*<<< orphan*/  rtc_cb (int /*<<< orphan*/ *) ; 

int32_t vfs_get_rtc( vfs_time *tm )
{
  if (rtc_cb) {
    return rtc_cb( tm );
  }

  return VFS_RES_ERR;
}