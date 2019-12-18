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
struct frame_rate_option {void* description; void* name; } ;
struct frame_rate_data {int /*<<< orphan*/  extra_options; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_PROPERTY_FRAME_RATE ; 
 void* bstrdup (char const*) ; 
 struct frame_rate_option* da_insert_new (int /*<<< orphan*/ ,size_t) ; 
 struct frame_rate_data* get_type_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void obs_property_frame_rate_option_insert(obs_property_t *p, size_t idx,
					   const char *name,
					   const char *description)
{
	struct frame_rate_data *data =
		get_type_data(p, OBS_PROPERTY_FRAME_RATE);
	if (!data)
		return;

	struct frame_rate_option *opt = da_insert_new(data->extra_options, idx);

	opt->name = bstrdup(name);
	opt->description = bstrdup(description);
}