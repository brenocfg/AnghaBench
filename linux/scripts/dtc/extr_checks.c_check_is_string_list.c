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
struct dt_info {int dummy; } ;
struct check {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_PROP (struct check*,struct dt_info*,struct node*,struct property*,char*) ; 
 struct property* get_property (struct node*,char*) ; 
 int strnlen (char*,int) ; 

__attribute__((used)) static void check_is_string_list(struct check *c, struct dt_info *dti,
				 struct node *node)
{
	int rem, l;
	struct property *prop;
	char *propname = c->data;
	char *str;

	prop = get_property(node, propname);
	if (!prop)
		return; /* Not present, assumed ok */

	str = prop->val.val;
	rem = prop->val.len;
	while (rem > 0) {
		l = strnlen(str, rem);
		if (l == rem) {
			FAIL_PROP(c, dti, node, prop, "property is not a string list");
			break;
		}
		rem -= l + 1;
		str += l + 1;
	}
}