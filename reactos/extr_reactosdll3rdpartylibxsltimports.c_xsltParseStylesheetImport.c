#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/ * xsltSecurityPrefsPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_10__ {int /*<<< orphan*/  URL; } ;
struct TYPE_9__ {struct TYPE_9__* parent; struct TYPE_9__* imports; struct TYPE_9__* next; int /*<<< orphan*/  dict; TYPE_8__* doc; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_LOAD_STYLESHEET ; 
 int /*<<< orphan*/  XSLT_PARSE_OPTIONS ; 
 int /*<<< orphan*/ * xmlBuildURI (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlGetNsProp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlNodeGetBase (TYPE_8__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xsltCheckRead (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xsltDocDefaultLoader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltFixImportedCompSteps (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * xsltGetDefaultSecurityPrefs () ; 
 TYPE_1__* xsltParseStylesheetImportedDoc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*,...) ; 

int
xsltParseStylesheetImport(xsltStylesheetPtr style, xmlNodePtr cur) {
    int ret = -1;
    xmlDocPtr import = NULL;
    xmlChar *base = NULL;
    xmlChar *uriRef = NULL;
    xmlChar *URI = NULL;
    xsltStylesheetPtr res;
    xsltSecurityPrefsPtr sec;

    if ((cur == NULL) || (style == NULL))
	return (ret);

    uriRef = xmlGetNsProp(cur, (const xmlChar *)"href", NULL);
    if (uriRef == NULL) {
	xsltTransformError(NULL, style, cur,
	    "xsl:import : missing href attribute\n");
	goto error;
    }

    base = xmlNodeGetBase(style->doc, cur);
    URI = xmlBuildURI(uriRef, base);
    if (URI == NULL) {
	xsltTransformError(NULL, style, cur,
	    "xsl:import : invalid URI reference %s\n", uriRef);
	goto error;
    }

    res = style;
    while (res != NULL) {
        if (res->doc == NULL)
	    break;
	if (xmlStrEqual(res->doc->URL, URI)) {
	    xsltTransformError(NULL, style, cur,
	       "xsl:import : recursion detected on imported URL %s\n", URI);
	    goto error;
	}
	res = res->parent;
    }

    /*
     * Security framework check
     */
    sec = xsltGetDefaultSecurityPrefs();
    if (sec != NULL) {
	int secres;

	secres = xsltCheckRead(sec, NULL, URI);
	if (secres == 0) {
	    xsltTransformError(NULL, NULL, NULL,
		 "xsl:import: read rights for %s denied\n",
			     URI);
	    goto error;
	}
    }

    import = xsltDocDefaultLoader(URI, style->dict, XSLT_PARSE_OPTIONS,
                                  (void *) style, XSLT_LOAD_STYLESHEET);
    if (import == NULL) {
	xsltTransformError(NULL, style, cur,
	    "xsl:import : unable to load %s\n", URI);
	goto error;
    }

    res = xsltParseStylesheetImportedDoc(import, style);
    if (res != NULL) {
	res->next = style->imports;
	style->imports = res;
	if (style->parent == NULL) {
	    xsltFixImportedCompSteps(style, res);
	}
	ret = 0;
    } else {
	xmlFreeDoc(import);
	}

error:
    if (uriRef != NULL)
	xmlFree(uriRef);
    if (base != NULL)
	xmlFree(base);
    if (URI != NULL)
	xmlFree(URI);

    return (ret);
}