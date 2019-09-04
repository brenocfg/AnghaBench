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
struct obs_properties {int /*<<< orphan*/  first_property; int /*<<< orphan*/ * last; } ;
typedef  struct obs_properties obs_properties_t ;

/* Variables and functions */
 struct obs_properties* bzalloc (int) ; 

obs_properties_t *obs_properties_create(void)
{
	struct obs_properties *props;
	props = bzalloc(sizeof(struct obs_properties));
	props->last = &props->first_property;
	return props;
}