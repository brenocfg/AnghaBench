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
struct obs_property {int enabled; int visible; int type; void* desc; void* name; struct obs_properties* parent; } ;
struct obs_properties {int dummy; } ;
typedef  enum obs_property_type { ____Placeholder_obs_property_type } obs_property_type ;

/* Variables and functions */
 void* bstrdup (char const*) ; 
 struct obs_property* bzalloc (int) ; 
 size_t get_property_size (int) ; 
 int /*<<< orphan*/  propertes_add (struct obs_properties*,struct obs_property*) ; 

__attribute__((used)) static inline struct obs_property *new_prop(struct obs_properties *props,
					    const char *name, const char *desc,
					    enum obs_property_type type)
{
	size_t data_size = get_property_size(type);
	struct obs_property *p;

	p = bzalloc(sizeof(struct obs_property) + data_size);
	p->parent = props;
	p->enabled = true;
	p->visible = true;
	p->type = type;
	p->name = bstrdup(name);
	p->desc = bstrdup(desc);
	propertes_add(props, p);

	return p;
}