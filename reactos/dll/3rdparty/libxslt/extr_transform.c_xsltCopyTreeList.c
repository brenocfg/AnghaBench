#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformContextPtr ;
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_10__ {struct TYPE_10__* next; } ;

/* Variables and functions */
 TYPE_1__* xsltCopyTree (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,TYPE_1__*,int,int) ; 

__attribute__((used)) static xmlNodePtr
xsltCopyTreeList(xsltTransformContextPtr ctxt, xmlNodePtr invocNode,
		 xmlNodePtr list,
		 xmlNodePtr insert, int isLRE, int topElemVisited)
{
    xmlNodePtr copy, ret = NULL;

    while (list != NULL) {
	copy = xsltCopyTree(ctxt, invocNode,
	    list, insert, isLRE, topElemVisited);
	if (copy != NULL) {
	    if (ret == NULL) {
		ret = copy;
	    }
	}
	list = list->next;
    }
    return(ret);
}