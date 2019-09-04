#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xmlXPathParserContextPtr ;
typedef  TYPE_4__* xmlXPathObjectPtr ;
typedef  TYPE_5__* xmlNsPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_23__ {int /*<<< orphan*/ * href; } ;
struct TYPE_22__ {int /*<<< orphan*/  stringval; } ;
struct TYPE_21__ {int /*<<< orphan*/  context; int /*<<< orphan*/  error; TYPE_1__* value; } ;
struct TYPE_20__ {TYPE_14__* inst; } ;
struct TYPE_19__ {scalar_t__ type; } ;
struct TYPE_18__ {int /*<<< orphan*/  doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPATH_INVALID_ARITY ; 
 int /*<<< orphan*/  XPATH_INVALID_TYPE ; 
 scalar_t__ XPATH_STRING ; 
 TYPE_4__* valuePop (TYPE_3__*) ; 
 int /*<<< orphan*/  valuePush (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 TYPE_5__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_14__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlSplitQName2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_4__*) ; 
 int /*<<< orphan*/  xmlXPathNewBoolean (int) ; 
 int /*<<< orphan*/ * xmlXPathNsLookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlXPathStringFunction (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * xsltExtElementLookup (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* xsltXPathGetTransformContext (TYPE_3__*) ; 

void
xsltElementAvailableFunction(xmlXPathParserContextPtr ctxt, int nargs){
    xmlXPathObjectPtr obj;
    xmlChar *prefix, *name;
    const xmlChar *nsURI = NULL;
    xsltTransformContextPtr tctxt;

    if (nargs != 1) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"element-available() : expects one string arg\n");
	ctxt->error = XPATH_INVALID_ARITY;
	return;
    }
    xmlXPathStringFunction(ctxt, 1);
    if ((ctxt->value == NULL) || (ctxt->value->type != XPATH_STRING)) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
	    "element-available() : invalid arg expecting a string\n");
	ctxt->error = XPATH_INVALID_TYPE;
	return;
    }
    obj = valuePop(ctxt);
    tctxt = xsltXPathGetTransformContext(ctxt);
    if ((tctxt == NULL) || (tctxt->inst == NULL)) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"element-available() : internal error tctxt == NULL\n");
	xmlXPathFreeObject(obj);
	valuePush(ctxt, xmlXPathNewBoolean(0));
	return;
    }


    name = xmlSplitQName2(obj->stringval, &prefix);
    if (name == NULL) {
	xmlNsPtr ns;

	name = xmlStrdup(obj->stringval);
	ns = xmlSearchNs(tctxt->inst->doc, tctxt->inst, NULL);
	if (ns != NULL) nsURI = ns->href;
    } else {
	nsURI = xmlXPathNsLookup(ctxt->context, prefix);
	if (nsURI == NULL) {
	    xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"element-available() : prefix %s is not bound\n", prefix);
	}
    }

    if (xsltExtElementLookup(tctxt, name, nsURI) != NULL) {
	valuePush(ctxt, xmlXPathNewBoolean(1));
    } else {
	valuePush(ctxt, xmlXPathNewBoolean(0));
    }

    xmlXPathFreeObject(obj);
    if (name != NULL)
	xmlFree(name);
    if (prefix != NULL)
	xmlFree(prefix);
}