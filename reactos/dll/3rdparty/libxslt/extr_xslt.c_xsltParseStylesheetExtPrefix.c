#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_14__ {scalar_t__ type; } ;
struct TYPE_13__ {int /*<<< orphan*/  href; } ;
struct TYPE_12__ {int /*<<< orphan*/  warnings; int /*<<< orphan*/  doc; } ;

/* Variables and functions */
 scalar_t__ IS_BLANK (scalar_t__) ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/ * XSLT_NAMESPACE ; 
 int /*<<< orphan*/  xmlFree (scalar_t__*) ; 
 scalar_t__* xmlGetNsProp (TYPE_3__*,scalar_t__ const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__*) ; 
 scalar_t__ xmlStrEqual (scalar_t__*,scalar_t__ const*) ; 
 scalar_t__* xmlStrndup (scalar_t__*,int) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltRegisterExtPrefix (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,char*,scalar_t__*) ; 

__attribute__((used)) static void
xsltParseStylesheetExtPrefix(xsltStylesheetPtr style, xmlNodePtr cur,
			     int isXsltElem) {
    xmlChar *prefixes;
    xmlChar *prefix, *end;

    if ((cur == NULL) || (style == NULL) || (cur->type != XML_ELEMENT_NODE))
	return;

    if (isXsltElem) {
	/* For xsl:stylesheet/xsl:transform. */
	prefixes = xmlGetNsProp(cur,
	    (const xmlChar *)"extension-element-prefixes", NULL);
    } else {
	/* For literal result elements and extension instructions. */
	prefixes = xmlGetNsProp(cur,
	    (const xmlChar *)"extension-element-prefixes", XSLT_NAMESPACE);
    }
    if (prefixes == NULL) {
	return;
    }

    prefix = prefixes;
    while (*prefix != 0) {
	while (IS_BLANK(*prefix)) prefix++;
	if (*prefix == 0)
	    break;
        end = prefix;
	while ((*end != 0) && (!IS_BLANK(*end))) end++;
	prefix = xmlStrndup(prefix, end - prefix);
	if (prefix) {
	    xmlNsPtr ns;

	    if (xmlStrEqual(prefix, (const xmlChar *)"#default"))
		ns = xmlSearchNs(style->doc, cur, NULL);
	    else
		ns = xmlSearchNs(style->doc, cur, prefix);
	    if (ns == NULL) {
		xsltTransformError(NULL, style, cur,
	    "xsl:extension-element-prefix : undefined namespace %s\n",
	                         prefix);
		if (style != NULL) style->warnings++;
	    } else {
#ifdef WITH_XSLT_DEBUG_PARSING
		xsltGenericDebug(xsltGenericDebugContext,
		    "add extension prefix %s\n", prefix);
#endif
		xsltRegisterExtPrefix(style, prefix, ns->href);
	    }
	    xmlFree(prefix);
	}
	prefix = end;
    }
    xmlFree(prefixes);
}