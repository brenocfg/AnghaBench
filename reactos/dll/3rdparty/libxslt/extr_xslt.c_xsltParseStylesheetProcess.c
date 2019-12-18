#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTemplatePtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  TYPE_3__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_19__ {int /*<<< orphan*/  children; } ;
struct TYPE_18__ {int literal_result; int forwards_compatible; TYPE_1__* templates; int /*<<< orphan*/  warnings; int /*<<< orphan*/  nopreproc; } ;
struct TYPE_17__ {int /*<<< orphan*/  content; int /*<<< orphan*/ * elem; int /*<<< orphan*/  match; struct TYPE_17__* next; } ;

/* Variables and functions */
 scalar_t__ IS_XSLT_ELEM (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_XSLT_NAME (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  XSLT_NAMESPACE ; 
 int /*<<< orphan*/ * xmlDocGetRootElement (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlGetNsProp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlStrdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltAddTemplate (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltInitGlobals () ; 
 TYPE_1__* xsltNewTemplate () ; 
 int /*<<< orphan*/  xsltParseStylesheetExcludePrefix (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xsltParseStylesheetExtPrefix (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xsltParseStylesheetTop (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltParseTemplateContent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltPreprocessStylesheet (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,char*) ; 

xsltStylesheetPtr
xsltParseStylesheetProcess(xsltStylesheetPtr ret, xmlDocPtr doc) {
    xmlNodePtr cur;

    xsltInitGlobals();

    if (doc == NULL)
	return(NULL);
    if (ret == NULL)
	return(ret);

    /*
     * First steps, remove blank nodes,
     * locate the xsl:stylesheet element and the
     * namespace declaration.
     */
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
	xsltTransformError(NULL, ret, (xmlNodePtr) doc,
		"xsltParseStylesheetProcess : empty stylesheet\n");
	return(NULL);
    }

    if ((IS_XSLT_ELEM(cur)) &&
	((IS_XSLT_NAME(cur, "stylesheet")) ||
	 (IS_XSLT_NAME(cur, "transform")))) {
#ifdef WITH_XSLT_DEBUG_PARSING
	xsltGenericDebug(xsltGenericDebugContext,
		"xsltParseStylesheetProcess : found stylesheet\n");
#endif
	ret->literal_result = 0;
	xsltParseStylesheetExcludePrefix(ret, cur, 1);
	xsltParseStylesheetExtPrefix(ret, cur, 1);
    } else {
	xsltParseStylesheetExcludePrefix(ret, cur, 0);
	xsltParseStylesheetExtPrefix(ret, cur, 0);
	ret->literal_result = 1;
    }
    if (!ret->nopreproc) {
	xsltPreprocessStylesheet(ret, cur);
    }
    if (ret->literal_result == 0) {
	xsltParseStylesheetTop(ret, cur);
    } else {
	xmlChar *prop;
	xsltTemplatePtr template;

	/*
	 * the document itself might be the template, check xsl:version
	 */
	prop = xmlGetNsProp(cur, (const xmlChar *)"version", XSLT_NAMESPACE);
	if (prop == NULL) {
	    xsltTransformError(NULL, ret, cur,
		"xsltParseStylesheetProcess : document is not a stylesheet\n");
	    return(NULL);
	}

#ifdef WITH_XSLT_DEBUG_PARSING
        xsltGenericDebug(xsltGenericDebugContext,
		"xsltParseStylesheetProcess : document is stylesheet\n");
#endif

	if ((!xmlStrEqual(prop, (const xmlChar *)"1.0")) &&
            (!xmlStrEqual(prop, (const xmlChar *)"1.1"))) {
	    xsltTransformError(NULL, ret, cur,
		"xsl:version: only 1.1 features are supported\n");
            ret->forwards_compatible = 1;
	    ret->warnings++;
	}
	xmlFree(prop);

	/*
	 * Create and link the template
	 */
	template = xsltNewTemplate();
	if (template == NULL) {
	    return(NULL);
	}
	template->next = ret->templates;
	ret->templates = template;
	template->match = xmlStrdup((const xmlChar *)"/");

	/*
	 * parse the content and register the pattern
	 */
	xsltParseTemplateContent(ret, (xmlNodePtr) doc);
	template->elem = (xmlNodePtr) doc;
	template->content = doc->children;
	xsltAddTemplate(ret, template, NULL, NULL);
	ret->literal_result = 1;
    }

    return(ret);
}