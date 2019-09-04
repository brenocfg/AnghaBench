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
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
struct TYPE_7__ {int /*<<< orphan*/ * stripSpaces; } ;
struct TYPE_6__ {TYPE_2__* style; } ;

/* Variables and functions */
 TYPE_2__* xsltNextImport (TYPE_2__*) ; 

int
xsltNeedElemSpaceHandling(xsltTransformContextPtr ctxt) {
    xsltStylesheetPtr style;

    if (ctxt == NULL)
	return(0);
    style = ctxt->style;
    while (style != NULL) {
	if (style->stripSpaces != NULL)
	    return(1);
	style = xsltNextImport(style);
    }
    return(0);
}