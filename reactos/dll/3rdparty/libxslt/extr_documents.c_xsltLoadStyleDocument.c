#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/ * xsltSecurityPrefsPtr ;
typedef  TYPE_3__* xsltDocumentPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_10__ {struct TYPE_10__* next; TYPE_1__* doc; } ;
struct TYPE_9__ {int /*<<< orphan*/  dict; TYPE_3__* docList; } ;
struct TYPE_8__ {int /*<<< orphan*/ * URL; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_LOAD_STYLESHEET ; 
 int /*<<< orphan*/  XSLT_PARSE_OPTIONS ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int xsltCheckRead (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xsltDocDefaultLoader (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xsltGetDefaultSecurityPrefs () ; 
 TYPE_3__* xsltNewStyleDocument (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 

xsltDocumentPtr
xsltLoadStyleDocument(xsltStylesheetPtr style, const xmlChar *URI) {
    xsltDocumentPtr ret;
    xmlDocPtr doc;
    xsltSecurityPrefsPtr sec;

    if ((style == NULL) || (URI == NULL))
	return(NULL);

    /*
     * Security framework check
     */
    sec = xsltGetDefaultSecurityPrefs();
    if (sec != NULL) {
	int res;

	res = xsltCheckRead(sec, NULL, URI);
	if (res == 0) {
	    xsltTransformError(NULL, NULL, NULL,
		 "xsltLoadStyleDocument: read rights for %s denied\n",
			     URI);
	    return(NULL);
	}
    }

    /*
     * Walk the context list to find the document if preparsed
     */
    ret = style->docList;
    while (ret != NULL) {
	if ((ret->doc != NULL) && (ret->doc->URL != NULL) &&
	    (xmlStrEqual(ret->doc->URL, URI)))
	    return(ret);
	ret = ret->next;
    }

    doc = xsltDocDefaultLoader(URI, style->dict, XSLT_PARSE_OPTIONS,
                               (void *) style, XSLT_LOAD_STYLESHEET);
    if (doc == NULL)
	return(NULL);

    ret = xsltNewStyleDocument(style, doc);
    return(ret);
}