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
struct frame_rate_option {void* description; void* name; } ;
struct TYPE_2__ {size_t num; } ;
struct frame_rate_data {TYPE_1__ extra_options; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  OBS_PROPERTY_FRAME_RATE ; 
 void* bstrdup (char const*) ; 
 struct frame_rate_option* da_push_back_new (TYPE_1__) ; 
 struct frame_rate_data* get_type_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t obs_property_frame_rate_option_add(obs_property_t *p, const char *name,
					  const char *description)
{
	struct frame_rate_data *data =
		get_type_data(p, OBS_PROPERTY_FRAME_RATE);
	if (!data)
		return DARRAY_INVALID;

	struct frame_rate_option *opt = da_push_back_new(data->extra_options);

	opt->name = bstrdup(name);
	opt->description = bstrdup(description);

	return data->extra_options.num - 1;
}