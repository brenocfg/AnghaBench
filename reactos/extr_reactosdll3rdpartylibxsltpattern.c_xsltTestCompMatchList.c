#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltTransformContextPtr ;
typedef  TYPE_1__* xsltCompMatchPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int xsltTestCompMatch (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xsltTestCompMatchList(xsltTransformContextPtr ctxt, xmlNodePtr node,
	              xsltCompMatchPtr comp) {
    int ret;

    if ((ctxt == NULL) || (node == NULL))
	return(-1);
    while (comp != NULL) {
	ret = xsltTestCompMatch(ctxt, comp, node, NULL, NULL);
	if (ret == 1)
	    return(1);
	comp = comp->next;
    }
    return(0);
}