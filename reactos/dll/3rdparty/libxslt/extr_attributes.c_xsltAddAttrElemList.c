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
typedef  TYPE_1__* xsltAttrElemPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
struct TYPE_5__ {struct TYPE_5__* next; } ;

/* Variables and functions */
 TYPE_1__* xsltNewAttrElem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xsltAttrElemPtr
xsltAddAttrElemList(xsltAttrElemPtr list, xmlNodePtr attr) {
    xsltAttrElemPtr next, cur;

    if (attr == NULL)
	return(list);
    if (list == NULL)
	return(xsltNewAttrElem(attr));
    cur = list;
    while (cur != NULL) {
	next = cur->next;
	if (next == NULL) {
	    cur->next = xsltNewAttrElem(attr);
	    return(list);
	}
	cur = next;
    }
    return(list);
}