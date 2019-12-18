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
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_12__ {int /*<<< orphan*/  doc; } ;
struct TYPE_11__ {scalar_t__ const* href; } ;
struct TYPE_10__ {int /*<<< orphan*/  dict; int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 scalar_t__ const* XML_XML_NAMESPACE ; 
 scalar_t__* xmlDictLookup (int /*<<< orphan*/ ,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 TYPE_2__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__*) ; 
 scalar_t__* xmlStrndup (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*,scalar_t__ const*,...) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,char*,scalar_t__*) ; 

const xmlChar *
xsltGetQNameURI2(xsltStylesheetPtr style, xmlNodePtr node,
		 const xmlChar **name) {
    int len = 0;
    xmlChar *qname;
    xmlNsPtr ns;

    if (name == NULL)
        return(NULL);
    qname = (xmlChar *)*name;
    if ((qname == NULL) || (*qname == 0))
        return(NULL);
    if (node == NULL) {
        xsltGenericError(xsltGenericErrorContext,
                         "QName: no element for namespace lookup %s\n",
                          qname);
	*name = NULL;
	return(NULL);
    }

    /*
     * we are not trying to validate but just to cut, and yes it will
     * work even if this is a set of UTF-8 encoded chars
     */
    while ((qname[len] != 0) && (qname[len] != ':'))
        len++;

    if (qname[len] == 0)
        return(NULL);

    /*
     * handle xml: separately, this one is magical
     */
    if ((qname[0] == 'x') && (qname[1] == 'm') &&
        (qname[2] == 'l') && (qname[3] == ':')) {
        if (qname[4] == 0)
            return(NULL);
        *name = xmlDictLookup(style->dict, &qname[4], -1);
        return(XML_XML_NAMESPACE);
    }

    qname = xmlStrndup(*name, len);
    ns = xmlSearchNs(node->doc, node, qname);
    if (ns == NULL) {
	if (style) {
	    xsltTransformError(NULL, style, node,
		"No namespace bound to prefix '%s'.\n",
		qname);
	    style->errors++;
	} else {
	    xsltGenericError(xsltGenericErrorContext,
                "%s : no namespace bound to prefix %s\n",
		*name, qname);
	}
        *name = NULL;
        xmlFree(qname);
        return(NULL);
    }
    *name = xmlDictLookup(style->dict, (*name)+len+1, -1);
    xmlFree(qname);
    return(ns->href);
}