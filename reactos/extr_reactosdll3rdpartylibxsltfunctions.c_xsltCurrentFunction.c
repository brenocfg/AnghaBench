#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xmlXPathParserContextPtr ;
struct TYPE_9__ {int /*<<< orphan*/  error; } ;
struct TYPE_8__ {int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPATH_INVALID_ARITY ; 
 int /*<<< orphan*/  valuePush (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlXPathNewNodeSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* xsltXPathGetTransformContext (TYPE_2__*) ; 

__attribute__((used)) static void
xsltCurrentFunction(xmlXPathParserContextPtr ctxt, int nargs){
    xsltTransformContextPtr tctxt;

    if (nargs != 0) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"current() : function uses no argument\n");
	ctxt->error = XPATH_INVALID_ARITY;
	return;
    }
    tctxt = xsltXPathGetTransformContext(ctxt);
    if (tctxt == NULL) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"current() : internal error tctxt == NULL\n");
	valuePush(ctxt, xmlXPathNewNodeSet(NULL));
    } else {
	valuePush(ctxt, xmlXPathNewNodeSet(tctxt->node)); /* current */
    }
}