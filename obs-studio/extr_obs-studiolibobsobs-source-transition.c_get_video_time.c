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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  obs_source_t ;
struct TYPE_3__ {int /*<<< orphan*/  video_time; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
 float calc_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* obs ; 

__attribute__((used)) static inline float get_video_time(obs_source_t *transition)
{
	uint64_t ts = obs->video.video_time;
	return calc_time(transition, ts);
}