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
struct foo_obj {int baz; int bar; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct foo_attribute {TYPE_1__ attr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtoint (char const*,int,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t b_store(struct foo_obj *foo_obj, struct foo_attribute *attr,
		       const char *buf, size_t count)
{
	int var, ret;

	ret = kstrtoint(buf, 10, &var);
	if (ret < 0)
		return ret;

	if (strcmp(attr->attr.name, "baz") == 0)
		foo_obj->baz = var;
	else
		foo_obj->bar = var;
	return count;
}