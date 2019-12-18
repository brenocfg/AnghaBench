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
struct obs_properties {int dummy; } ;
typedef  struct obs_properties obs_properties_t ;

/* Variables and functions */
 struct obs_properties* obs_properties_create () ; 
 int /*<<< orphan*/  obs_properties_set_param (struct obs_properties*,void*,void (*) (void*)) ; 

obs_properties_t *obs_properties_create_param(void *param,
					      void (*destroy)(void *param))
{
	struct obs_properties *props = obs_properties_create();
	obs_properties_set_param(props, param, destroy);
	return props;
}