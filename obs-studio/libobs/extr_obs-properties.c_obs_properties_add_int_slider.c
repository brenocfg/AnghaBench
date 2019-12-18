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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_NUMBER_SLIDER ; 
 int /*<<< orphan*/ * add_int (int /*<<< orphan*/ *,char const*,char const*,int,int,int,int /*<<< orphan*/ ) ; 

obs_property_t *obs_properties_add_int_slider(obs_properties_t *props,
					      const char *name,
					      const char *desc, int min,
					      int max, int step)
{
	return add_int(props, name, desc, min, max, step, OBS_NUMBER_SLIDER);
}