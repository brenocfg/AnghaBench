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
struct TYPE_2__ {struct attribute** attrs; } ;
struct attribute_set {size_t members; size_t max_members; TYPE_1__ group; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 

__attribute__((used)) static int add_to_attr_set(struct attribute_set *s, struct attribute *attr)
{
	if (!s || !attr)
		return -EINVAL;

	if (s->members >= s->max_members)
		return -ENOMEM;

	s->group.attrs[s->members] = attr;
	s->members++;

	return 0;
}