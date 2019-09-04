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
struct attribute_set {int dummy; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 int add_to_attr_set (struct attribute_set*,struct attribute*) ; 

__attribute__((used)) static int add_many_to_attr_set(struct attribute_set *s,
			struct attribute **attr,
			unsigned int count)
{
	int i, res;

	for (i = 0; i < count; i++) {
		res = add_to_attr_set(s, attr[i]);
		if (res)
			return res;
	}

	return 0;
}