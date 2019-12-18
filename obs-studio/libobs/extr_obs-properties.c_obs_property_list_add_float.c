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
struct list_data {scalar_t__ format; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 scalar_t__ OBS_COMBO_FORMAT_FLOAT ; 
 size_t add_item (struct list_data*,char const*,double*) ; 
 struct list_data* get_list_data (int /*<<< orphan*/ *) ; 

size_t obs_property_list_add_float(obs_property_t *p, const char *name,
				   double val)
{
	struct list_data *data = get_list_data(p);
	if (data && data->format == OBS_COMBO_FORMAT_FLOAT)
		return add_item(data, name, &val);
	return 0;
}