#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlXPathParserContextPtr ;
typedef  TYPE_3__* xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/  const xmlChar ;
struct TYPE_12__ {int /*<<< orphan*/ * stringval; } ;
struct TYPE_11__ {int /*<<< orphan*/  context; int /*<<< orphan*/  error; TYPE_1__* value; } ;
struct TYPE_10__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPATH_INVALID_ARITY ; 
 int /*<<< orphan*/  XPATH_INVALID_TYPE ; 
 scalar_t__ XPATH_STRING ; 
 scalar_t__ XSLT_DEFAULT_URL ; 
 scalar_t__ XSLT_DEFAULT_VENDOR ; 
 scalar_t__ XSLT_DEFAULT_VERSION ; 
 int /*<<< orphan*/  const* XSLT_NAMESPACE ; 
 TYPE_3__* valuePop (TYPE_2__*) ; 
 int /*<<< orphan*/  valuePush (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* xmlSplitQName2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* xmlStrdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlXPathNewString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* xmlXPathNsLookup (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  xsltXPathGetTransformContext (TYPE_2__*) ; 

void
xsltSystemPropertyFunction(xmlXPathParserContextPtr ctxt, int nargs){
    xmlXPathObjectPtr obj;
    xmlChar *prefix, *name;
    const xmlChar *nsURI = NULL;

    if (nargs != 1) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"system-property() : expects one string arg\n");
	ctxt->error = XPATH_INVALID_ARITY;
	return;
    }
    if ((ctxt->value == NULL) || (ctxt->value->type != XPATH_STRING)) {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
	    "system-property() : invalid arg expecting a string\n");
	ctxt->error = XPATH_INVALID_TYPE;
	return;
    }
    obj = valuePop(ctxt);
    if (obj->stringval == NULL) {
	valuePush(ctxt, xmlXPathNewString((const xmlChar *)""));
    } else {
	name = xmlSplitQName2(obj->stringval, &prefix);
	if (name == NULL) {
	    name = xmlStrdup(obj->stringval);
	} else {
	    nsURI = xmlXPathNsLookup(ctxt->context, prefix);
	    if (nsURI == NULL) {
		xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		    "system-property() : prefix %s is not bound\n", prefix);
	    }
	}

	if (xmlStrEqual(nsURI, XSLT_NAMESPACE)) {
#ifdef DOCBOOK_XSL_HACK
	    if (xmlStrEqual(name, (const xmlChar *)"vendor")) {
		xsltStylesheetPtr sheet;
		xsltTransformContextPtr tctxt;

		tctxt = xsltXPathGetTransformContext(ctxt);
		if ((tctxt != NULL) && (tctxt->inst != NULL) &&
		    (xmlStrEqual(tctxt->inst->name, BAD_CAST "variable")) &&
		    (tctxt->inst->parent != NULL) &&
		    (xmlStrEqual(tctxt->inst->parent->name,
				 BAD_CAST "template")))
		    sheet = tctxt->style;
		else
		    sheet = NULL;
		if ((sheet != NULL) && (sheet->doc != NULL) &&
		    (sheet->doc->URL != NULL) &&
		    (xmlStrstr(sheet->doc->URL,
			       (const xmlChar *)"chunk") != NULL)) {
		    valuePush(ctxt, xmlXPathNewString(
			(const xmlChar *)"libxslt (SAXON 6.2 compatible)"));

		} else {
		    valuePush(ctxt, xmlXPathNewString(
			(const xmlChar *)XSLT_DEFAULT_VENDOR));
		}
	    } else
#else
	    if (xmlStrEqual(name, (const xmlChar *)"vendor")) {
		valuePush(ctxt, xmlXPathNewString(
			  (const xmlChar *)XSLT_DEFAULT_VENDOR));
	    } else
#endif
	    if (xmlStrEqual(name, (const xmlChar *)"version")) {
		valuePush(ctxt, xmlXPathNewString(
		    (const xmlChar *)XSLT_DEFAULT_VERSION));
	    } else if (xmlStrEqual(name, (const xmlChar *)"vendor-url")) {
		valuePush(ctxt, xmlXPathNewString(
		    (const xmlChar *)XSLT_DEFAULT_URL));
	    } else {
		valuePush(ctxt, xmlXPathNewString((const xmlChar *)""));
	    }
	} else {
	    valuePush(ctxt, xmlXPathNewString((const xmlChar *)""));
        }
	if (name != NULL)
	    xmlFree(name);
	if (prefix != NULL)
	    xmlFree(prefix);
    }
    xmlXPathFreeObject(obj);
}