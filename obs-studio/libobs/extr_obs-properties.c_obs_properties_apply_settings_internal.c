#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct obs_property {scalar_t__ type; struct obs_property* next; int /*<<< orphan*/  priv; int /*<<< orphan*/  (* modified2 ) (int /*<<< orphan*/ ,TYPE_1__*,struct obs_property*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* modified ) (TYPE_1__*,struct obs_property*,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {struct obs_property* first_property; } ;
typedef  TYPE_1__ obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 scalar_t__ OBS_PROPERTY_GROUP ; 
 TYPE_1__* obs_property_group_content (struct obs_property*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct obs_property*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,struct obs_property*,int /*<<< orphan*/ *) ; 

void obs_properties_apply_settings_internal(obs_properties_t *props,
					    obs_data_t *settings,
					    obs_properties_t *realprops)
{
	struct obs_property *p;

	p = props->first_property;
	while (p) {
		if (p->type == OBS_PROPERTY_GROUP) {
			obs_properties_apply_settings_internal(
				obs_property_group_content(p), settings,
				realprops);
		}
		if (p->modified)
			p->modified(realprops, p, settings);
		else if (p->modified2)
			p->modified2(p->priv, realprops, p, settings);
		p = p->next;
	}
}