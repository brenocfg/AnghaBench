#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltStylesheetPtr ;
typedef  TYPE_4__* xsltAttrSetPtr ;
typedef  TYPE_5__* xsltAttrElemPtr ;
typedef  TYPE_6__* xmlNsPtr ;
typedef  TYPE_7__* xmlNodePtr ;
typedef  scalar_t__ xmlChar ;
typedef  TYPE_8__* xmlAttrPtr ;
struct TYPE_30__ {TYPE_1__* children; } ;
struct TYPE_29__ {scalar_t__ type; int /*<<< orphan*/  doc; } ;
struct TYPE_28__ {scalar_t__* href; } ;
struct TYPE_27__ {struct TYPE_27__* next; TYPE_13__* attr; } ;
struct TYPE_26__ {TYPE_5__* attrs; } ;
struct TYPE_25__ {int /*<<< orphan*/ * attributeSets; } ;
struct TYPE_24__ {scalar_t__ debugStatus; TYPE_3__* style; int /*<<< orphan*/  dict; } ;
struct TYPE_23__ {scalar_t__* content; } ;
struct TYPE_22__ {int /*<<< orphan*/  psvi; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ IS_BLANK (scalar_t__ const) ; 
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 scalar_t__ XSLT_DEBUG_NONE ; 
 scalar_t__* xmlDictLookup (int /*<<< orphan*/ ,scalar_t__ const*,int) ; 
 TYPE_4__* xmlHashLookup2 (int /*<<< orphan*/ *,scalar_t__ const*,scalar_t__ const*) ; 
 TYPE_6__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_7__*,scalar_t__ const*) ; 
 scalar_t__ xmlValidateQName (scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xslHandleDebugger (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltAttribute (TYPE_2__*,TYPE_7__*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,scalar_t__ const*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 scalar_t__* xsltSplitQName (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const**) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,TYPE_7__*,char*,scalar_t__ const*,...) ; 

void
xsltApplyAttributeSet(xsltTransformContextPtr ctxt, xmlNodePtr node,
                      xmlNodePtr inst,
                      const xmlChar *attrSets)
{
    const xmlChar *ncname = NULL;
    const xmlChar *prefix = NULL;
    const xmlChar *curstr, *endstr;
    xsltAttrSetPtr set;
    xsltStylesheetPtr style;

    if (attrSets == NULL) {
	if (inst == NULL)
	    return;
	else {
	    /*
	    * Extract the value from @inst.
	    */
	    if (inst->type == XML_ATTRIBUTE_NODE) {
		if ( ((xmlAttrPtr) inst)->children != NULL)
		    attrSets = ((xmlAttrPtr) inst)->children->content;

	    }
	    if (attrSets == NULL) {
		/*
		* TODO: Return an error?
		*/
		return;
	    }
	}
    }
    /*
    * Parse/apply the list of QNames.
    */
    curstr = attrSets;
    while (*curstr != 0) {
        while (IS_BLANK(*curstr))
            curstr++;
        if (*curstr == 0)
            break;
        endstr = curstr;
        while ((*endstr != 0) && (!IS_BLANK(*endstr)))
            endstr++;
        curstr = xmlDictLookup(ctxt->dict, curstr, endstr - curstr);
        if (curstr) {
            xmlNsPtr ns;
            const xmlChar *nsUri = NULL;

#ifdef WITH_XSLT_DEBUG_ATTRIBUTES
            xsltGenericDebug(xsltGenericDebugContext,
                             "apply attribute set %s\n", curstr);
#endif

            if (xmlValidateQName(curstr, 0)) {
                xsltTransformError(ctxt, NULL, inst,
                    "The name '%s' in use-attribute-sets is not a valid "
                    "QName.\n", curstr);
                return;
            }

            ncname = xsltSplitQName(ctxt->dict, curstr, &prefix);
            if (prefix != NULL) {
	        ns = xmlSearchNs(inst->doc, inst, prefix);
                if (ns == NULL) {
                    xsltTransformError(ctxt, NULL, inst,
                        "use-attribute-set : No namespace found for QName "
                        "'%s:%s'\n", prefix, ncname);
                    return;
                }
                nsUri = ns->href;
            }

            style = ctxt->style;

#ifdef WITH_DEBUGGER
            if ((style != NULL) &&
		(style->attributeSets != NULL) &&
		(ctxt->debugStatus != XSLT_DEBUG_NONE))
	    {
                set = xmlHashLookup2(style->attributeSets, ncname, nsUri);
                if ((set != NULL) && (set->attrs != NULL) &&
                    (set->attrs->attr != NULL))
                    xslHandleDebugger(set->attrs->attr->parent, node, NULL,
			ctxt);
            }
#endif
	    /*
	    * Lookup the referenced attribute-set. All attribute sets were
            * moved to the top stylesheet so there's no need to iterate
            * imported stylesheets
	    */
            set = xmlHashLookup2(style->attributeSets, ncname, nsUri);
            if (set != NULL) {
                xsltAttrElemPtr cur = set->attrs;
                while (cur != NULL) {
                    if (cur->attr != NULL) {
                        xsltAttribute(ctxt, node, cur->attr,
                            cur->attr->psvi);
                    }
                    cur = cur->next;
                }
            }
        }
        curstr = endstr;
    }
}