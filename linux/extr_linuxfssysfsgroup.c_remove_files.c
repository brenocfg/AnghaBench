#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kernfs_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct bin_attribute {TYPE_1__ attr; } ;
struct attribute_group {struct bin_attribute** bin_attrs; struct attribute** attrs; } ;
struct attribute {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernfs_remove_by_name (struct kernfs_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_files(struct kernfs_node *parent,
			 const struct attribute_group *grp)
{
	struct attribute *const *attr;
	struct bin_attribute *const *bin_attr;

	if (grp->attrs)
		for (attr = grp->attrs; *attr; attr++)
			kernfs_remove_by_name(parent, (*attr)->name);
	if (grp->bin_attrs)
		for (bin_attr = grp->bin_attrs; *bin_attr; bin_attr++)
			kernfs_remove_by_name(parent, (*bin_attr)->attr.name);
}