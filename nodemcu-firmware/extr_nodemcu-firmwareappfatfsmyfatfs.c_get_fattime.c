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
struct TYPE_3__ {int year; int mon; int day; int hour; int min; int sec; } ;
typedef  TYPE_1__ vfs_time ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ FF_NORTC_MDAY ; 
 scalar_t__ FF_NORTC_MON ; 
 int FF_NORTC_YEAR ; 
 scalar_t__ VFS_RES_OK ; 
 scalar_t__ vfs_get_rtc (TYPE_1__*) ; 

DWORD get_fattime( void )
{
  DWORD stamp;
  vfs_time tm;

  if (VFS_RES_OK == vfs_get_rtc( &tm )) {
    // sanity checks
    tm.year = (tm.year >= 1980) && (tm.year < 2108) ? tm.year : 1980;
    tm.mon  = (tm.mon  >= 1) && (tm.mon  <= 12) ? tm.mon  : 1;
    tm.day  = (tm.day  >= 1) && (tm.day  <= 31) ? tm.day  : 1;
    tm.hour = (tm.hour >= 0) && (tm.hour <= 23) ? tm.hour : 0;
    tm.min  = (tm.min  >= 0) && (tm.min  <= 59) ? tm.min  : 0;
    tm.sec  = (tm.sec  >= 0) && (tm.sec  <= 59) ? tm.sec  : 0;

    stamp = (tm.year-1980) << 25 | tm.mon << 21 | tm.day << 16 |
            tm.hour << 11 | tm.min << 5 | tm.sec;
  } else {
    // default time stamp derived from ffconf.h
    stamp = ((DWORD)(FF_NORTC_YEAR - 1980) << 25 | (DWORD)FF_NORTC_MON << 21 | (DWORD)FF_NORTC_MDAY << 16);
  }

  return stamp;
}