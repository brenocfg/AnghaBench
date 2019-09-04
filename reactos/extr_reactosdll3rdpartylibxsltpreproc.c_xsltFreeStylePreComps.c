#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xsltStylePreCompPtr ;
typedef  TYPE_2__* xsltElemPreCompPtr ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  (* free ) (TYPE_2__*) ;struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* preComps; } ;

/* Variables and functions */
 scalar_t__ XSLT_FUNC_EXTENSION ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltFreeStylePreComp (int /*<<< orphan*/ ) ; 

void
xsltFreeStylePreComps(xsltStylesheetPtr style) {
    xsltElemPreCompPtr cur, next;

    if (style == NULL)
	return;

    cur = style->preComps;
    while (cur != NULL) {
	next = cur->next;
	if (cur->type == XSLT_FUNC_EXTENSION)
	    cur->free(cur);
	else
	    xsltFreeStylePreComp((xsltStylePreCompPtr) cur);
	cur = next;
    }
}