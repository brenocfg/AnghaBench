#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float x; float y; } ;
struct TYPE_5__ {float x; float y; } ;
struct TYPE_4__ {float x; float y; } ;
struct scroll_filter_data {TYPE_3__ offset; TYPE_2__ scroll_speed; TYPE_1__ size_i; } ;

/* Variables and functions */

__attribute__((used)) static void scroll_filter_tick(void *data, float seconds)
{
	struct scroll_filter_data *filter = data;

	filter->offset.x += filter->size_i.x * filter->scroll_speed.x * seconds;
	filter->offset.y += filter->size_i.y * filter->scroll_speed.y * seconds;

	if (filter->offset.x > 1.0f)
		filter->offset.x -= 1.0f;
	if (filter->offset.y > 1.0f)
		filter->offset.y -= 1.0f;
}