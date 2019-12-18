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
struct obs_property {int type; } ;
typedef  enum obs_property_type { ____Placeholder_obs_property_type } obs_property_type ;

/* Variables and functions */
 void* get_property_data (struct obs_property*) ; 

__attribute__((used)) static inline void *get_type_data(struct obs_property *prop,
				  enum obs_property_type type)
{
	if (!prop || prop->type != type)
		return NULL;

	return get_property_data(prop);
}