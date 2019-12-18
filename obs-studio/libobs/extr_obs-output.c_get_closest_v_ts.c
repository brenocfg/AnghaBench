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
typedef  int uint64_t ;
struct pause_data {int last_video_ts; } ;
struct TYPE_3__ {int video_frame_interval_ns; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
 TYPE_2__* obs ; 
 int os_gettime_ns () ; 

__attribute__((used)) static inline uint64_t get_closest_v_ts(struct pause_data *pause)
{
	uint64_t interval = obs->video.video_frame_interval_ns;
	uint64_t i2 = interval * 2;
	uint64_t ts = os_gettime_ns();

	return pause->last_video_ts +
	       ((ts - pause->last_video_ts + i2) / interval) * interval;
}