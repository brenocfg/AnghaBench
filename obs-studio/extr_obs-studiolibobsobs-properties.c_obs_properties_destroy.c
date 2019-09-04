#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_property {struct obs_property* next; } ;
struct TYPE_4__ {scalar_t__ param; int /*<<< orphan*/  (* destroy ) (scalar_t__) ;struct obs_property* first_property; } ;
typedef  TYPE_1__ obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_property_destroy (struct obs_property*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void obs_properties_destroy(obs_properties_t *props)
{
	if (props) {
		struct obs_property *p = props->first_property;

		if (props->destroy && props->param)
			props->destroy(props->param);

		while (p) {
			struct obs_property *next = p->next;
			obs_property_destroy(p);
			p = next;
		}

		bfree(props);
	}
}