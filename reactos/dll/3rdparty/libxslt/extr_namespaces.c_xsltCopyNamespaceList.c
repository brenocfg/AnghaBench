#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xsltTransformContextPtr ;
typedef  TYPE_4__* xmlNsPtr ;
typedef  TYPE_5__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_18__ {scalar_t__ type; int /*<<< orphan*/  doc; TYPE_1__* ns; } ;
struct TYPE_17__ {scalar_t__ type; struct TYPE_17__* next; int /*<<< orphan*/  const* prefix; int /*<<< orphan*/  const* href; } ;
struct TYPE_16__ {TYPE_2__* style; } ;
struct TYPE_15__ {int /*<<< orphan*/  nsAliases; } ;
struct TYPE_14__ {int /*<<< orphan*/  const* href; int /*<<< orphan*/  const* prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* UNDEFINED_DEFAULT_NS ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_NAMESPACE_DECL ; 
 int /*<<< orphan*/  const* XSLT_NAMESPACE ; 
 scalar_t__ xmlHashLookup (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 TYPE_4__* xmlNewNs (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_4__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

xmlNsPtr
xsltCopyNamespaceList(xsltTransformContextPtr ctxt, xmlNodePtr node,
	              xmlNsPtr cur) {
    xmlNsPtr ret = NULL, tmp;
    xmlNsPtr p = NULL,q;

    if (cur == NULL)
	return(NULL);
    if (cur->type != XML_NAMESPACE_DECL)
	return(NULL);

    /*
     * One can add namespaces only on element nodes
     */
    if ((node != NULL) && (node->type != XML_ELEMENT_NODE))
	node = NULL;

    while (cur != NULL) {
	if (cur->type != XML_NAMESPACE_DECL)
	    break;

	/*
	 * Avoid duplicating namespace declarations in the tree if
	 * a matching declaration is in scope.
	 */
	if (node != NULL) {
	    if ((node->ns != NULL) &&
		(xmlStrEqual(node->ns->prefix, cur->prefix)) &&
	(xmlStrEqual(node->ns->href, cur->href))) {
		cur = cur->next;
		continue;
	    }
	    tmp = xmlSearchNs(node->doc, node, cur->prefix);
	    if ((tmp != NULL) && (xmlStrEqual(tmp->href, cur->href))) {
		cur = cur->next;
		continue;
	    }
	}
#ifdef XSLT_REFACTORED
	/*
	* Namespace exclusion and ns-aliasing is performed at
	* compilation-time in the refactored code.
	*/
	q = xmlNewNs(node, cur->href, cur->prefix);
	if (p == NULL) {
	    ret = p = q;
	} else {
	    p->next = q;
	    p = q;
	}
#else
	/*
	* TODO: Remove this if the refactored code gets enabled.
	*/
	if (!xmlStrEqual(cur->href, XSLT_NAMESPACE)) {
	    const xmlChar *URI;
	    /* TODO apply cascading */
	    URI = (const xmlChar *) xmlHashLookup(ctxt->style->nsAliases,
		                                  cur->href);
	    if (URI == UNDEFINED_DEFAULT_NS) {
		cur = cur->next;
	        continue;
	    }
	    if (URI != NULL) {
		q = xmlNewNs(node, URI, cur->prefix);
	    } else {
		q = xmlNewNs(node, cur->href, cur->prefix);
	    }
	    if (p == NULL) {
		ret = p = q;
	    } else {
		p->next = q;
		p = q;
	    }
	}
#endif
	cur = cur->next;
    }
    return(ret);
}