#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltStyleItemCopyPtr ;
typedef  int /*<<< orphan*/  xsltElemPreCompPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlAttrPtr ;
struct TYPE_32__ {int type; int /*<<< orphan*/  children; int /*<<< orphan*/  content; int /*<<< orphan*/  name; int /*<<< orphan*/  doc; } ;
struct TYPE_31__ {int /*<<< orphan*/ * use; } ;
struct TYPE_30__ {TYPE_3__* insert; int /*<<< orphan*/  node; } ;

/* Variables and functions */
#define  XML_ATTRIBUTE_NODE 136 
#define  XML_CDATA_SECTION_NODE 135 
#define  XML_COMMENT_NODE 134 
#define  XML_DOCUMENT_NODE 133 
#define  XML_ELEMENT_NODE 132 
#define  XML_HTML_DOCUMENT_NODE 131 
#define  XML_NAMESPACE_DECL 130 
#define  XML_PI_NODE 129 
#define  XML_TEXT_NODE 128 
 int /*<<< orphan*/  XSLT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSLT_TRACE_COPY ; 
 TYPE_3__* xmlNewComment (int /*<<< orphan*/ ) ; 
 TYPE_3__* xmlNewDocPI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* xsltAddChild (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  xsltApplyAttributeSet (TYPE_1__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltApplySequenceConstructor (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltCopyText (TYPE_1__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltShallowCopyAttr (TYPE_1__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* xsltShallowCopyElem (TYPE_1__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltShallowCopyNsNode (TYPE_1__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

void
xsltCopy(xsltTransformContextPtr ctxt, xmlNodePtr node,
	 xmlNodePtr inst, xsltElemPreCompPtr castedComp)
{
#ifdef XSLT_REFACTORED
    xsltStyleItemCopyPtr comp = (xsltStyleItemCopyPtr) castedComp;
#else
    xsltStylePreCompPtr comp = (xsltStylePreCompPtr) castedComp;
#endif
    xmlNodePtr copy, oldInsert;

    oldInsert = ctxt->insert;
    if (ctxt->insert != NULL) {
	switch (node->type) {
	    case XML_TEXT_NODE:
	    case XML_CDATA_SECTION_NODE:
		/*
		 * This text comes from the stylesheet
		 * For stylesheets, the set of whitespace-preserving
		 * element names consists of just xsl:text.
		 */
#ifdef WITH_XSLT_DEBUG_PROCESS
		if (node->type == XML_CDATA_SECTION_NODE) {
		    XSLT_TRACE(ctxt,XSLT_TRACE_COPY,xsltGenericDebug(xsltGenericDebugContext,
			 "xsltCopy: CDATA text %s\n", node->content));
		} else {
		    XSLT_TRACE(ctxt,XSLT_TRACE_COPY,xsltGenericDebug(xsltGenericDebugContext,
			 "xsltCopy: text %s\n", node->content));
                }
#endif
		xsltCopyText(ctxt, ctxt->insert, node, 0);
		break;
	    case XML_DOCUMENT_NODE:
	    case XML_HTML_DOCUMENT_NODE:
		break;
	    case XML_ELEMENT_NODE:
		/*
		* REVISIT NOTE: The "fake" is a doc-node, not an element node.
		* REMOVED:
		*   if (xmlStrEqual(node->name, BAD_CAST " fake node libxslt"))
		*    return;
		*/

#ifdef WITH_XSLT_DEBUG_PROCESS
		XSLT_TRACE(ctxt,XSLT_TRACE_COPY,xsltGenericDebug(xsltGenericDebugContext,
				 "xsltCopy: node %s\n", node->name));
#endif
		copy = xsltShallowCopyElem(ctxt, node, ctxt->insert, 0);
		ctxt->insert = copy;
		if (comp->use != NULL) {
		    xsltApplyAttributeSet(ctxt, node, inst, comp->use);
		}
		break;
	    case XML_ATTRIBUTE_NODE: {
#ifdef WITH_XSLT_DEBUG_PROCESS
		XSLT_TRACE(ctxt,XSLT_TRACE_COPY,xsltGenericDebug(xsltGenericDebugContext,
				 "xsltCopy: attribute %s\n", node->name));
#endif
		/*
		* REVISIT: We could also raise an error if the parent is not
		* an element node.
		* OPTIMIZE TODO: Can we set the value/children of the
		* attribute without an intermediate copy of the string value?
		*/
		xsltShallowCopyAttr(ctxt, inst, ctxt->insert, (xmlAttrPtr) node);
		break;
	    }
	    case XML_PI_NODE:
#ifdef WITH_XSLT_DEBUG_PROCESS
		XSLT_TRACE(ctxt,XSLT_TRACE_COPY,xsltGenericDebug(xsltGenericDebugContext,
				 "xsltCopy: PI %s\n", node->name));
#endif
		copy = xmlNewDocPI(ctxt->insert->doc, node->name,
		                   node->content);
		copy = xsltAddChild(ctxt->insert, copy);
		break;
	    case XML_COMMENT_NODE:
#ifdef WITH_XSLT_DEBUG_PROCESS
		XSLT_TRACE(ctxt,XSLT_TRACE_COPY,xsltGenericDebug(xsltGenericDebugContext,
				 "xsltCopy: comment\n"));
#endif
		copy = xmlNewComment(node->content);
		copy = xsltAddChild(ctxt->insert, copy);
		break;
	    case XML_NAMESPACE_DECL:
#ifdef WITH_XSLT_DEBUG_PROCESS
		XSLT_TRACE(ctxt,XSLT_TRACE_COPY,xsltGenericDebug(xsltGenericDebugContext,
				 "xsltCopy: namespace declaration\n"));
#endif
		xsltShallowCopyNsNode(ctxt, inst, ctxt->insert, (xmlNsPtr)node);
		break;
	    default:
		break;

	}
    }

    switch (node->type) {
	case XML_DOCUMENT_NODE:
	case XML_HTML_DOCUMENT_NODE:
	case XML_ELEMENT_NODE:
	    xsltApplySequenceConstructor(ctxt, ctxt->node, inst->children,
		NULL);
	    break;
	default:
	    break;
    }
    ctxt->insert = oldInsert;
}