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
struct group_data {int /*<<< orphan*/ * content; } ;
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_PROPERTY_GROUP ; 
 struct group_data* get_type_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

obs_properties_t *obs_property_group_content(obs_property_t *p)
{
	struct group_data *data = get_type_data(p, OBS_PROPERTY_GROUP);
	return data ? data->content : NULL;
}