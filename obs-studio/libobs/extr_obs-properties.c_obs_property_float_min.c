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
struct float_data {double min; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_PROPERTY_FLOAT ; 
 struct float_data* get_type_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

double obs_property_float_min(obs_property_t *p)
{
	struct float_data *data = get_type_data(p, OBS_PROPERTY_FLOAT);
	return data ? data->min : 0;
}