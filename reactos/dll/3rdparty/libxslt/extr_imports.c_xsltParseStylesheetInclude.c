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

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltStyleItemIncludePtr ;
typedef  TYPE_3__* xsltDocumentPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  TYPE_5__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_23__ {int /*<<< orphan*/  URL; } ;
struct TYPE_22__ {int /*<<< orphan*/ * psvi; } ;
struct TYPE_21__ {int preproc; struct TYPE_21__* includes; TYPE_5__* doc; } ;
struct TYPE_20__ {TYPE_3__* include; } ;
struct TYPE_19__ {int nopreproc; TYPE_5__* doc; TYPE_3__* includes; int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 scalar_t__ IS_XSLT_ELEM_FAST (TYPE_4__*) ; 
 int /*<<< orphan*/ * xmlBuildURI (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlGetNsProp (TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlNodeGetBase (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* xsltLoadStyleDocument (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* xsltParseStylesheetProcess (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_4__*,char*,...) ; 

int
xsltParseStylesheetInclude(xsltStylesheetPtr style, xmlNodePtr cur) {
    int ret = -1;
    xmlDocPtr oldDoc;
    xmlChar *base = NULL;
    xmlChar *uriRef = NULL;
    xmlChar *URI = NULL;
    xsltStylesheetPtr result;
    xsltDocumentPtr include;
    xsltDocumentPtr docptr;
    int oldNopreproc;

    if ((cur == NULL) || (style == NULL))
	return (ret);

    uriRef = xmlGetNsProp(cur, (const xmlChar *)"href", NULL);
    if (uriRef == NULL) {
	xsltTransformError(NULL, style, cur,
	    "xsl:include : missing href attribute\n");
	goto error;
    }

    base = xmlNodeGetBase(style->doc, cur);
    URI = xmlBuildURI(uriRef, base);
    if (URI == NULL) {
	xsltTransformError(NULL, style, cur,
	    "xsl:include : invalid URI reference %s\n", uriRef);
	goto error;
    }

    /*
     * in order to detect recursion, we check all previously included
     * stylesheets.
     */
    docptr = style->includes;
    while (docptr != NULL) {
        if (xmlStrEqual(docptr->doc->URL, URI)) {
	    xsltTransformError(NULL, style, cur,
	        "xsl:include : recursion detected on included URL %s\n", URI);
	    goto error;
	}
	docptr = docptr->includes;
    }

    include = xsltLoadStyleDocument(style, URI);
    if (include == NULL) {
	xsltTransformError(NULL, style, cur,
	    "xsl:include : unable to load %s\n", URI);
	goto error;
    }
#ifdef XSLT_REFACTORED
    if (IS_XSLT_ELEM_FAST(cur) && (cur->psvi != NULL)) {
	((xsltStyleItemIncludePtr) cur->psvi)->include = include;
    } else {
	xsltTransformError(NULL, style, cur,
	    "Internal error: (xsltParseStylesheetInclude) "
	    "The xsl:include element was not compiled.\n", URI);
	style->errors++;
    }
#endif
    oldDoc = style->doc;
    style->doc = include->doc;
    /* chain to stylesheet for recursion checking */
    include->includes = style->includes;
    style->includes = include;
    oldNopreproc = style->nopreproc;
    style->nopreproc = include->preproc;
    /*
    * TODO: This will change some values of the
    *  including stylesheet with every included module
    *  (e.g. excluded-result-prefixes)
    *  We need to strictly seperate such stylesheet-owned values.
    */
    result = xsltParseStylesheetProcess(style, include->doc);
    style->nopreproc = oldNopreproc;
    include->preproc = 1;
    style->includes = include->includes;
    style->doc = oldDoc;
    if (result == NULL) {
	ret = -1;
	goto error;
    }
    ret = 0;

error:
    if (uriRef != NULL)
	xmlFree(uriRef);
    if (base != NULL)
	xmlFree(base);
    if (URI != NULL)
	xmlFree(URI);

    return (ret);
}