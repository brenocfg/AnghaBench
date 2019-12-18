#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltDocumentPtr ;
typedef  int /*<<< orphan*/  xmlXPathParserContextPtr ;
typedef  TYPE_4__* xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/ * xmlXPathContextPtr ;
typedef  TYPE_5__* xmlURIPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  TYPE_6__* xmlDocPtr ;
typedef  char xmlChar ;
struct TYPE_24__ {int /*<<< orphan*/  URL; } ;
struct TYPE_23__ {int /*<<< orphan*/ * fragment; } ;
struct TYPE_22__ {int type; } ;
struct TYPE_21__ {TYPE_6__* doc; } ;
struct TYPE_20__ {TYPE_1__* style; } ;
struct TYPE_19__ {TYPE_6__* doc; } ;

/* Variables and functions */
#define  XPATH_BOOLEAN 137 
#define  XPATH_LOCATIONSET 136 
#define  XPATH_NODESET 135 
#define  XPATH_NUMBER 134 
#define  XPATH_POINT 133 
#define  XPATH_RANGE 132 
#define  XPATH_STRING 131 
#define  XPATH_UNDEFINED 130 
#define  XPATH_USERS 129 
#define  XPATH_XSLT_TREE 128 
 int /*<<< orphan*/  valuePush (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 int /*<<< orphan*/  xmlFreeURI (TYPE_5__*) ; 
 TYPE_5__* xmlParseURI (char const*) ; 
 char* xmlSaveUri (TYPE_5__*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlXPathFreeContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_4__*) ; 
 TYPE_4__* xmlXPathNewNodeSet (int /*<<< orphan*/ *) ; 
 TYPE_4__* xmlXPtrEval (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlXPtrNewContext (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* xsltLoadDocument (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* xsltXPathGetTransformContext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xsltDocumentFunctionLoadDocument(xmlXPathParserContextPtr ctxt, xmlChar* URI)
{
    xsltTransformContextPtr tctxt;
    xmlURIPtr uri;
    xmlChar *fragment;
    xsltDocumentPtr idoc; /* document info */
    xmlDocPtr doc;
    xmlXPathContextPtr xptrctxt = NULL;
    xmlXPathObjectPtr resObj = NULL;

    tctxt = xsltXPathGetTransformContext(ctxt);
    if (tctxt == NULL) {
	xsltTransformError(NULL, NULL, NULL,
	    "document() : internal error tctxt == NULL\n");
	valuePush(ctxt, xmlXPathNewNodeSet(NULL));
	return;
    }

    uri = xmlParseURI((const char *) URI);
    if (uri == NULL) {
	xsltTransformError(tctxt, NULL, NULL,
	    "document() : failed to parse URI\n");
	valuePush(ctxt, xmlXPathNewNodeSet(NULL));
	return;
    }

    /*
     * check for and remove fragment identifier
     */
    fragment = (xmlChar *)uri->fragment;
    if (fragment != NULL) {
        xmlChar *newURI;
	uri->fragment = NULL;
	newURI = xmlSaveUri(uri);
	idoc = xsltLoadDocument(tctxt, newURI);
	xmlFree(newURI);
    } else
	idoc = xsltLoadDocument(tctxt, URI);
    xmlFreeURI(uri);

    if (idoc == NULL) {
	if ((URI == NULL) ||
	    (URI[0] == '#') ||
	    ((tctxt->style->doc != NULL) &&
	    (xmlStrEqual(tctxt->style->doc->URL, URI))))
	{
	    /*
	    * This selects the stylesheet's doc itself.
	    */
	    doc = tctxt->style->doc;
	} else {
	    valuePush(ctxt, xmlXPathNewNodeSet(NULL));

	    if (fragment != NULL)
		xmlFree(fragment);

	    return;
	}
    } else
	doc = idoc->doc;

    if (fragment == NULL) {
	valuePush(ctxt, xmlXPathNewNodeSet((xmlNodePtr) doc));
	return;
    }

    /* use XPointer of HTML location for fragment ID */
#ifdef LIBXML_XPTR_ENABLED
    xptrctxt = xmlXPtrNewContext(doc, NULL, NULL);
    if (xptrctxt == NULL) {
	xsltTransformError(tctxt, NULL, NULL,
	    "document() : internal error xptrctxt == NULL\n");
	goto out_fragment;
    }

    resObj = xmlXPtrEval(fragment, xptrctxt);
    xmlXPathFreeContext(xptrctxt);
#endif

    if (resObj == NULL)
	goto out_fragment;

    switch (resObj->type) {
	case XPATH_NODESET:
	    break;
	case XPATH_UNDEFINED:
	case XPATH_BOOLEAN:
	case XPATH_NUMBER:
	case XPATH_STRING:
	case XPATH_POINT:
	case XPATH_USERS:
	case XPATH_XSLT_TREE:
	case XPATH_RANGE:
	case XPATH_LOCATIONSET:
	    xsltTransformError(tctxt, NULL, NULL,
		"document() : XPointer does not select a node set: #%s\n",
		fragment);
	goto out_object;
    }

    valuePush(ctxt, resObj);
    xmlFree(fragment);
    return;

out_object:
    xmlXPathFreeObject(resObj);

out_fragment:
    valuePush(ctxt, xmlXPathNewNodeSet(NULL));
    xmlFree(fragment);
}