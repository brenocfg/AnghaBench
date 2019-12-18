#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
struct TYPE_13__ {scalar_t__ type; int /*<<< orphan*/  doc; TYPE_1__* ns; } ;
struct TYPE_12__ {scalar_t__ type; struct TYPE_12__* next; int /*<<< orphan*/  prefix; int /*<<< orphan*/  href; } ;
struct TYPE_11__ {int /*<<< orphan*/  href; int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 TYPE_2__* xmlNewNs (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xmlNsPtr
xsltCopyNamespaceListInternal(xmlNodePtr elem, xmlNsPtr ns) {
    xmlNsPtr ret = NULL;
    xmlNsPtr p = NULL, q, luNs;

    if (ns == NULL)
	return(NULL);
    /*
     * One can add namespaces only on element nodes
     */
    if ((elem != NULL) && (elem->type != XML_ELEMENT_NODE))
	elem = NULL;

    do {
	if (ns->type != XML_NAMESPACE_DECL)
	    break;
	/*
	 * Avoid duplicating namespace declarations on the tree.
	 */
	if (elem != NULL) {
	    if ((elem->ns != NULL) &&
		xmlStrEqual(elem->ns->prefix, ns->prefix) &&
		xmlStrEqual(elem->ns->href, ns->href))
	    {
		ns = ns->next;
		continue;
	    }
	    luNs = xmlSearchNs(elem->doc, elem, ns->prefix);
	    if ((luNs != NULL) && (xmlStrEqual(luNs->href, ns->href)))
	    {
		ns = ns->next;
		continue;
	    }
	}
	q = xmlNewNs(elem, ns->href, ns->prefix);
	if (p == NULL) {
	    ret = p = q;
	} else if (q != NULL) {
	    p->next = q;
	    p = q;
	}
	ns = ns->next;
    } while (ns != NULL);
    return(ret);
}