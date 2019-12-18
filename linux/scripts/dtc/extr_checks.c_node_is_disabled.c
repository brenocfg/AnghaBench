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
struct TYPE_2__ {char* val; } ;
struct property {TYPE_1__ val; } ;
struct node {int dummy; } ;

/* Variables and functions */
 struct property* get_property (struct node*,char*) ; 
 scalar_t__ streq (char*,char*) ; 

__attribute__((used)) static bool node_is_disabled(struct node *node)
{
	struct property *prop;

	prop = get_property(node, "status");
	if (prop) {
		char *str = prop->val.val;
		if (streq("disabled", str))
			return true;
	}

	return false;
}