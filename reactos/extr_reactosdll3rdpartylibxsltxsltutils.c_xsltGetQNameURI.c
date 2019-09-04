#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_7__ {int /*<<< orphan*/  doc; } ;
struct TYPE_6__ {scalar_t__ const* href; } ;

/* Variables and functions */
 scalar_t__ const* XML_XML_NAMESPACE ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 TYPE_1__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__*) ; 
 scalar_t__* xmlStrdup (scalar_t__*) ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 

const xmlChar *
xsltGetQNameURI(xmlNodePtr node, xmlChar ** name)
{
    int len = 0;
    xmlChar *qname;
    xmlNsPtr ns;

    if (name == NULL)
	return(NULL);
    qname = *name;
    if ((qname == NULL) || (*qname == 0))
	return(NULL);
    if (node == NULL) {
	xsltGenericError(xsltGenericErrorContext,
		         "QName: no element for namespace lookup %s\n",
			 qname);
	xmlFree(qname);
	*name = NULL;
	return(NULL);
    }

    /* nasty but valid */
    if (qname[0] == ':')
	return(NULL);

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
        *name = xmlStrdup(&qname[4]);
	xmlFree(qname);
	return(XML_XML_NAMESPACE);
    }

    qname[len] = 0;
    ns = xmlSearchNs(node->doc, node, qname);
    if (ns == NULL) {
	xsltGenericError(xsltGenericErrorContext,
		"%s:%s : no namespace bound to prefix %s\n",
		         qname, &qname[len + 1], qname);
	*name = NULL;
	xmlFree(qname);
	return(NULL);
    }
    *name = xmlStrdup(&qname[len + 1]);
    xmlFree(qname);
    return(ns->href);
}