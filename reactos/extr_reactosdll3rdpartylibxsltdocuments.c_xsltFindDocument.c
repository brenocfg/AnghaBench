#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltDocumentPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/ * doc; } ;
struct TYPE_7__ {TYPE_3__* document; TYPE_1__* style; TYPE_3__* docList; } ;
struct TYPE_6__ {int /*<<< orphan*/ * doc; } ;

/* Variables and functions */

xsltDocumentPtr
xsltFindDocument (xsltTransformContextPtr ctxt, xmlDocPtr doc) {
    xsltDocumentPtr ret;

    if ((ctxt == NULL) || (doc == NULL))
	return(NULL);

    /*
     * Walk the context list to find the document
     */
    ret = ctxt->docList;
    while (ret != NULL) {
	if (ret->doc == doc)
	    return(ret);
	ret = ret->next;
    }
    if (doc == ctxt->style->doc)
	return(ctxt->document);
    return(NULL);
}