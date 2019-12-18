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
struct TYPE_4__ {size_t num; TYPE_1__* array; } ;
struct frame_rate_data {TYPE_2__ extra_options; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_PROPERTY_FRAME_RATE ; 
 struct frame_rate_data* get_type_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const char *obs_property_frame_rate_option_name(obs_property_t *p, size_t idx)
{
	struct frame_rate_data *data =
		get_type_data(p, OBS_PROPERTY_FRAME_RATE);
	return data && data->extra_options.num > idx
		       ? data->extra_options.array[idx].name
		       : NULL;
}