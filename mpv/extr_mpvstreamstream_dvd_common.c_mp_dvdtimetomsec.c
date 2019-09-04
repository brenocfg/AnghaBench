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
struct TYPE_3__ {int frame_u; int hour; int minute; int second; } ;
typedef  TYPE_1__ dvd_time_t ;

/* Variables and functions */

int mp_dvdtimetomsec(dvd_time_t *dt)
{
  int framerates[4] = {0, 2500, 0, 2997};
  int framerate = framerates[(dt->frame_u & 0xc0) >> 6];
  int msec = (((dt->hour & 0xf0) >> 3) * 5 + (dt->hour & 0x0f)) * 3600000;
  msec += (((dt->minute & 0xf0) >> 3) * 5 + (dt->minute & 0x0f)) * 60000;
  msec += (((dt->second & 0xf0) >> 3) * 5 + (dt->second & 0x0f)) * 1000;
  if(framerate > 0)
    msec += (((dt->frame_u & 0x30) >> 3) * 5 + (dt->frame_u & 0x0f)) * 100000 / framerate;
  return msec;
}