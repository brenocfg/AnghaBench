#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlAttrPtr ;
struct TYPE_7__ {scalar_t__ name; } ;
struct TYPE_6__ {scalar_t__ href; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_1__* attr_find_ns (TYPE_2__*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int attr_is_equal_ex(xmlAttrPtr node, char *name, char *ns)
{
	if (name == NULL || strcmp((char*)node->name, name) == 0) {
		if (ns) {
			xmlNsPtr nsPtr = attr_find_ns(node);
			if (nsPtr) {
				return (strcmp((char*)nsPtr->href, ns) == 0);
			} else {
				return FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}