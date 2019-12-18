#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylesheetPtr ;
typedef  TYPE_3__* xmlNsPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  int /*<<< orphan*/  const xmlChar ;
struct TYPE_21__ {int /*<<< orphan*/  doc; } ;
struct TYPE_20__ {int /*<<< orphan*/ * prefix; int /*<<< orphan*/  const* href; } ;
struct TYPE_19__ {int /*<<< orphan*/ * nsAliases; } ;
struct TYPE_18__ {TYPE_2__* style; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* UNDEFINED_DEFAULT_NS ; 
 scalar_t__ xmlHashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_3__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* xsltGetSpecialNamespace (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_2__* xsltNextImport (TYPE_2__*) ; 

xmlNsPtr
xsltGetNamespace(xsltTransformContextPtr ctxt, xmlNodePtr cur, xmlNsPtr ns,
	         xmlNodePtr out)
{

    if (ns == NULL)
	return(NULL);

#ifdef XSLT_REFACTORED
    /*
    * Namespace exclusion and ns-aliasing is performed at
    * compilation-time in the refactored code.
    * Additionally, aliasing is not intended for non Literal
    * Result Elements.
    */
    return(xsltGetSpecialNamespace(ctxt, cur, ns->href, ns->prefix, out));
#else
    {
	xsltStylesheetPtr style;
	const xmlChar *URI = NULL; /* the replacement URI */

	if ((ctxt == NULL) || (cur == NULL) || (out == NULL))
	    return(NULL);

	style = ctxt->style;
	while (style != NULL) {
	    if (style->nsAliases != NULL)
		URI = (const xmlChar *)
		xmlHashLookup(style->nsAliases, ns->href);
	    if (URI != NULL)
		break;

	    style = xsltNextImport(style);
	}


	if (URI == UNDEFINED_DEFAULT_NS) {
	    return(xsltGetSpecialNamespace(ctxt, cur, NULL, NULL, out));
#if 0
	    /*
	    * TODO: Removed, since wrong. If there was no default
	    * namespace in the stylesheet then this must resolve to
	    * the NULL namespace.
	    */
	    xmlNsPtr dflt;
	    dflt = xmlSearchNs(cur->doc, cur, NULL);
	    if (dflt != NULL)
		URI = dflt->href;
	    else
		return NULL;
#endif
	} else if (URI == NULL)
	    URI = ns->href;

	return(xsltGetSpecialNamespace(ctxt, cur, URI, ns->prefix, out));
    }
#endif
}