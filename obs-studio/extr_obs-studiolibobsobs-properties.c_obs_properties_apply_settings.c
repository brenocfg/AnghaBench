#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct obs_property {struct obs_property* next; int /*<<< orphan*/  priv; int /*<<< orphan*/  (* modified2 ) (int /*<<< orphan*/ ,TYPE_1__*,struct obs_property*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* modified ) (TYPE_1__*,struct obs_property*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {struct obs_property* first_property; } ;
typedef  TYPE_1__ obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct obs_property*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*,struct obs_property*,int /*<<< orphan*/ *) ; 

void obs_properties_apply_settings(obs_properties_t *props, obs_data_t *settings)
{
	struct obs_property *p;

	if (!props)
		return;
	
	p = props->first_property;
	while (p) {
		if (p->modified)
			p->modified(props, p, settings);
		else if (p->modified2)
			p->modified2(p->priv, props, p, settings);
		p = p->next;
	}
}