#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ ** attrs; int /*<<< orphan*/  match; int /*<<< orphan*/ * class; } ;
struct TYPE_4__ {TYPE_3__ ac; } ;
struct raid_template {TYPE_1__ raid_attrs; } ;
struct raid_internal {struct raid_template r; int /*<<< orphan*/ ** attrs; struct raid_function_template* f; } ;
struct raid_function_template {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RAID_NUM_ATTRS ; 
 int /*<<< orphan*/  attribute_container_register (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_attr_level ; 
 int /*<<< orphan*/  dev_attr_resync ; 
 int /*<<< orphan*/  dev_attr_state ; 
 struct raid_internal* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ raid_class ; 
 int /*<<< orphan*/  raid_match ; 
 scalar_t__ unlikely (int) ; 

struct raid_template *
raid_class_attach(struct raid_function_template *ft)
{
	struct raid_internal *i = kzalloc(sizeof(struct raid_internal),
					  GFP_KERNEL);
	int count = 0;

	if (unlikely(!i))
		return NULL;

	i->f = ft;

	i->r.raid_attrs.ac.class = &raid_class.class;
	i->r.raid_attrs.ac.match = raid_match;
	i->r.raid_attrs.ac.attrs = &i->attrs[0];

	attribute_container_register(&i->r.raid_attrs.ac);

	i->attrs[count++] = &dev_attr_level;
	i->attrs[count++] = &dev_attr_resync;
	i->attrs[count++] = &dev_attr_state;

	i->attrs[count] = NULL;
	BUG_ON(count > RAID_NUM_ATTRS);

	return &i->r;
}