#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  TYPE_2__* xsltAttrSetPtr ;
typedef  TYPE_3__* xsltAttrElemPtr ;
struct TYPE_10__ {TYPE_1__* psvi; } ;
struct TYPE_9__ {struct TYPE_9__* next; TYPE_4__* attr; } ;
struct TYPE_8__ {TYPE_3__* attrs; } ;
struct TYPE_7__ {scalar_t__ name; scalar_t__ ns; } ;

/* Variables and functions */
 void* xsltNewAttrElem (TYPE_4__*) ; 

__attribute__((used)) static void
xsltMergeAttrSets(xsltAttrSetPtr set, xsltAttrSetPtr other) {
    xsltAttrElemPtr cur;
    xsltAttrElemPtr old = other->attrs;
    int add;

    while (old != NULL) {
	/*
	 * Check that the attribute is not yet in the list
	 */
	cur = set->attrs;
	add = 1;
	while (cur != NULL) {
            xsltStylePreCompPtr curComp = cur->attr->psvi;
            xsltStylePreCompPtr oldComp = old->attr->psvi;

            if ((curComp->name == oldComp->name) &&
                (curComp->ns == oldComp->ns)) {
                add = 0;
                break;
            }
	    if (cur->next == NULL)
		break;
            cur = cur->next;
	}

	if (add == 1) {
	    if (cur == NULL) {
		set->attrs = xsltNewAttrElem(old->attr);
	    } else if (add) {
		cur->next = xsltNewAttrElem(old->attr);
	    }
	}

	old = old->next;
    }
}