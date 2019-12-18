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
typedef  TYPE_2__* xmlXPathParserContextPtr ;
struct TYPE_6__ {TYPE_1__* value; int /*<<< orphan*/  error; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPATH_INVALID_ARITY ; 
 int /*<<< orphan*/  XPATH_INVALID_TYPE ; 
 scalar_t__ XPATH_NODESET ; 
 scalar_t__ XPATH_XSLT_TREE ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xsltXPathGetTransformContext (TYPE_2__*) ; 

void
xsltFunctionNodeSet(xmlXPathParserContextPtr ctxt, int nargs){
    if (nargs != 1) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"node-set() : expects one result-tree arg\n");
	ctxt->error = XPATH_INVALID_ARITY;
	return;
    }
    if ((ctxt->value == NULL) ||
	((ctxt->value->type != XPATH_XSLT_TREE) &&
	 (ctxt->value->type != XPATH_NODESET))) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
	    "node-set() invalid arg expecting a result tree\n");
	ctxt->error = XPATH_INVALID_TYPE;
	return;
    }
    if (ctxt->value->type == XPATH_XSLT_TREE) {
	ctxt->value->type = XPATH_NODESET;
    }
}