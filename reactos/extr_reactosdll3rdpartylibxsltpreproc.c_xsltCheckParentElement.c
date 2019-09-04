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
typedef  TYPE_3__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  const* name; struct TYPE_10__* parent; TYPE_1__* ns; } ;
struct TYPE_9__ {int /*<<< orphan*/  errors; int /*<<< orphan*/ * extInfos; scalar_t__ literal_result; } ;
struct TYPE_8__ {int /*<<< orphan*/  const* href; } ;

/* Variables and functions */
 scalar_t__ XML_DOCUMENT_NODE ; 
 int /*<<< orphan*/ * xmlHashLookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,char*,...) ; 

__attribute__((used)) static void
xsltCheckParentElement(xsltStylesheetPtr style, xmlNodePtr inst,
                       const xmlChar *allow1, const xmlChar *allow2) {
    xmlNodePtr parent;

    if ((style == NULL) || (inst == NULL) || (inst->ns == NULL) ||
        (style->literal_result))
        return;

    parent = inst->parent;
    if (parent == NULL) {
	xsltTransformError(NULL, style, inst,
		"internal problem: element has no parent\n");
	style->errors++;
	return;
    }
    if (((parent->ns == inst->ns) ||
	 ((parent->ns != NULL) &&
	  (xmlStrEqual(parent->ns->href, inst->ns->href)))) &&
	((xmlStrEqual(parent->name, allow1)) ||
	 (xmlStrEqual(parent->name, allow2)))) {
	return;
    }

    if (style->extInfos != NULL) {
	while ((parent != NULL) && (parent->type != XML_DOCUMENT_NODE)) {
	    /*
	     * if we are within an extension element all bets are off
	     * about the semantic there e.g. xsl:param within func:function
	     */
	    if ((parent->ns != NULL) &&
		(xmlHashLookup(style->extInfos, parent->ns->href) != NULL))
		return;

	    parent = parent->parent;
	}
    }
    xsltTransformError(NULL, style, inst,
		       "element %s is not allowed within that context\n",
		       inst->name);
    style->errors++;
}