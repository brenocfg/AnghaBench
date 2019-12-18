#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t num; TYPE_1__* array; } ;
struct TYPE_6__ {char const* name; TYPE_5__ children; } ;
typedef  TYPE_1__ profile_entry ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back_new (TYPE_5__) ; 
 TYPE_1__* init_entry (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static profile_entry *get_child(profile_entry *parent, const char *name)
{
	const size_t num = parent->children.num;
	for (size_t i = 0; i < num; i++) {
		profile_entry *child = &parent->children.array[i];
		if (child->name == name)
			return child;
	}

	return init_entry(da_push_back_new(parent->children), name);
}