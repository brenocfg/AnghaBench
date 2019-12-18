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
struct TYPE_2__ {char* val; int len; } ;
struct property {TYPE_1__ val; } ;
struct node {int dummy; } ;

/* Variables and functions */
 struct property* get_property (struct node*,char*) ; 
 scalar_t__ streq (char const*,char const*) ; 
 scalar_t__ strnlen (char const*,int) ; 

__attribute__((used)) static bool node_is_compatible(struct node *node, const char *compat)
{
	struct property *prop;
	const char *str, *end;

	prop = get_property(node, "compatible");
	if (!prop)
		return false;

	for (str = prop->val.val, end = str + prop->val.len; str < end;
	     str += strnlen(str, end - str) + 1) {
		if (streq(str, compat))
			return true;
	}
	return false;
}