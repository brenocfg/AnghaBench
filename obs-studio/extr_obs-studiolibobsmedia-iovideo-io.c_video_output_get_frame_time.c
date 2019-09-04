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
struct TYPE_3__ {int /*<<< orphan*/  frame_time; } ;
typedef  TYPE_1__ video_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

uint64_t video_output_get_frame_time(const video_t *video)
{
	return video ? video->frame_time : 0;
}