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
struct video_output_info {int dummy; } ;
struct TYPE_3__ {struct video_output_info const info; } ;
typedef  TYPE_1__ video_t ;

/* Variables and functions */

const struct video_output_info *video_output_get_info(const video_t *video)
{
	return video ? &video->info : NULL;
}