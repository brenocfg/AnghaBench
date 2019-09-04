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
struct obs_context_data {int type; } ;
typedef  enum obs_obj_type { ____Placeholder_obs_obj_type } obs_obj_type ;

/* Variables and functions */
 int OBS_OBJ_TYPE_INVALID ; 

enum obs_obj_type obs_obj_get_type(void *obj)
{
	struct obs_context_data *context = obj;
	return context ? context->type : OBS_OBJ_TYPE_INVALID;
}