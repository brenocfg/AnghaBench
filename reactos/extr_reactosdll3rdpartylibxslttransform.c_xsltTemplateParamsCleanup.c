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
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStackElemPtr ;
struct TYPE_6__ {scalar_t__ level; } ;
struct TYPE_5__ {int varsNr; int varsBase; TYPE_2__* vars; TYPE_2__** varsTab; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsltFreeStackElemList (TYPE_2__*) ; 

__attribute__((used)) static void
xsltTemplateParamsCleanup(xsltTransformContextPtr ctxt)
{
    xsltStackElemPtr param;

    for (; ctxt->varsNr > ctxt->varsBase; ctxt->varsNr--) {
	param = ctxt->varsTab[ctxt->varsNr -1];
	/*
	* Free xsl:param items.
	* xsl:with-param items will have a level of -1 or -2.
	*/
	if (param->level >= 0) {
	    xsltFreeStackElemList(param);
	}
    }
    if (ctxt->varsNr > 0)
        ctxt->vars = ctxt->varsTab[ctxt->varsNr - 1];
    else
        ctxt->vars = NULL;
}