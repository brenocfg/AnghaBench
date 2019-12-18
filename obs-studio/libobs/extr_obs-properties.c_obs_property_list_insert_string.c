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
 scalar_t__ OBS_COMBO_FORMAT_STRING ; 
 struct list_data* get_list_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_item (struct list_data*,size_t,char const*,char const*) ; 

void obs_property_list_insert_string(obs_property_t *p, size_t idx,
				     const char *name, const char *val)
{
	struct list_data *data = get_list_data(p);
	if (data && data->format == OBS_COMBO_FORMAT_STRING)
		insert_item(data, idx, name, val);
}