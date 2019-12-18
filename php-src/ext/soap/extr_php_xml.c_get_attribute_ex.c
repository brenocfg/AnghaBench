#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlAttrPtr ;
struct TYPE_5__ {struct TYPE_5__* next; } ;

/* Variables and functions */
 scalar_t__ attr_is_equal_ex (TYPE_1__*,char*,char*) ; 

xmlAttrPtr get_attribute_ex(xmlAttrPtr node, char *name, char *ns)
{
	while (node!=NULL) {
		if (attr_is_equal_ex(node, name, ns)) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}