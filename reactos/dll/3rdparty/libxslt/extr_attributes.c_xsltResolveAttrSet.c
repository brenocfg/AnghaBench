#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltAttrSetPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_16__ {scalar_t__ state; } ;
struct TYPE_15__ {int /*<<< orphan*/ * attributeSets; int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 scalar_t__ ATTRSET_RESOLVED ; 
 scalar_t__ ATTRSET_RESOLVING ; 
 TYPE_2__* xmlHashLookup2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlHashRemoveEntry2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltFreeAttrSet (TYPE_2__*) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltMergeAttrSets (TYPE_2__*,TYPE_2__*) ; 
 TYPE_1__* xsltNextImport (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltResolveUseAttrSets (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
xsltResolveAttrSet(xsltAttrSetPtr set, xsltStylesheetPtr topStyle,
                   xsltStylesheetPtr style, const xmlChar *name,
                   const xmlChar *ns, int depth) {
    xsltStylesheetPtr cur;
    xsltAttrSetPtr other;

    if (set->state == ATTRSET_RESOLVED)
        return;
    if (set->state == ATTRSET_RESOLVING) {
	xsltTransformError(NULL, topStyle, NULL,
            "xsl:attribute-set : use-attribute-sets recursion detected"
            " on %s\n", name);
        topStyle->errors++;
        set->state = ATTRSET_RESOLVED;
        return;
    }
    if (depth > 100) {
	xsltTransformError(NULL, topStyle, NULL,
		"xsl:attribute-set : use-attribute-sets maximum recursion "
		"depth exceeded on %s\n", name);
        topStyle->errors++;
	return;
    }

    set->state = ATTRSET_RESOLVING;

    xsltResolveUseAttrSets(set, topStyle, depth);

    /* Merge imported sets. */
    cur = xsltNextImport(style);
    while (cur != NULL) {
        if (cur->attributeSets != NULL) {
            other = xmlHashLookup2(cur->attributeSets, name, ns);

            if (other != NULL) {
#ifdef WITH_XSLT_DEBUG_ATTRIBUTES
                xsltGenericDebug(xsltGenericDebugContext,
                    "xsl:attribute-set : merging import for %s\n", name);
#endif
                xsltResolveUseAttrSets(other, topStyle, depth);
                xsltMergeAttrSets(set, other);
                xmlHashRemoveEntry2(cur->attributeSets, name, ns, NULL);
                xsltFreeAttrSet(other);
            }
        }

        cur = xsltNextImport(cur);
    }

    set->state = ATTRSET_RESOLVED;
}