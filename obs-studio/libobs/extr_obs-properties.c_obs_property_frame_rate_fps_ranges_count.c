#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; } ;
struct frame_rate_data {TYPE_1__ ranges; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_PROPERTY_FRAME_RATE ; 
 struct frame_rate_data* get_type_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t obs_property_frame_rate_fps_ranges_count(obs_property_t *p)
{
	struct frame_rate_data *data =
		get_type_data(p, OBS_PROPERTY_FRAME_RATE);
	return data ? data->ranges.num : 0;
}