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
struct kobject {int dummy; } ;
struct attribute_group {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int kobject_add (struct kobject*,struct kobject*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_init (struct kobject*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 struct kobject* kzalloc (int,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (struct kobject*,struct attribute_group const*) ; 
 int /*<<< orphan*/  widget_ktype ; 

__attribute__((used)) static int add_widget_node(struct kobject *parent, hda_nid_t nid,
			   const struct attribute_group *group,
			   struct kobject **res)
{
	struct kobject *kobj = kzalloc(sizeof(*kobj), GFP_KERNEL);
	int err;

	if (!kobj)
		return -ENOMEM;
	kobject_init(kobj, &widget_ktype);
	err = kobject_add(kobj, parent, "%02x", nid);
	if (err < 0)
		return err;
	err = sysfs_create_group(kobj, group);
	if (err < 0) {
		kobject_put(kobj);
		return err;
	}

	*res = kobj;
	return 0;
}