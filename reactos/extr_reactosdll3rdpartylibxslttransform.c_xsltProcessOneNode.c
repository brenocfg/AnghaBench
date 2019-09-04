#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltTemplatePtr ;
typedef  int /*<<< orphan*/  xsltStackElemPtr ;
typedef  TYPE_3__* xmlNodePtr ;
struct TYPE_16__ {scalar_t__ type; } ;
struct TYPE_15__ {int /*<<< orphan*/  content; } ;
struct TYPE_14__ {TYPE_2__* currentTemplateRule; TYPE_3__* node; } ;

/* Variables and functions */
 scalar_t__ XML_ATTRIBUTE_NODE ; 
 int /*<<< orphan*/  xsltApplyXSLTTemplate (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltDefaultProcessOneNode (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xsltGetTemplate (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

void
xsltProcessOneNode(xsltTransformContextPtr ctxt, xmlNodePtr contextNode,
	           xsltStackElemPtr withParams)
{
    xsltTemplatePtr templ;
    xmlNodePtr oldNode;

    templ = xsltGetTemplate(ctxt, contextNode, NULL);
    /*
     * If no template is found, apply the default rule.
     */
    if (templ == NULL) {
#ifdef WITH_XSLT_DEBUG_PROCESS
	if (contextNode->type == XML_DOCUMENT_NODE) {
	    XSLT_TRACE(ctxt,XSLT_TRACE_PROCESS_NODE,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltProcessOneNode: no template found for /\n"));
	} else if (contextNode->type == XML_CDATA_SECTION_NODE) {
	    XSLT_TRACE(ctxt,XSLT_TRACE_PROCESS_NODE,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltProcessOneNode: no template found for CDATA\n"));
	} else if (contextNode->type == XML_ATTRIBUTE_NODE) {
	    XSLT_TRACE(ctxt,XSLT_TRACE_PROCESS_NODE,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltProcessOneNode: no template found for attribute %s\n",
	                     ((xmlAttrPtr) contextNode)->name));
	} else  {
	    XSLT_TRACE(ctxt,XSLT_TRACE_PROCESS_NODE,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltProcessOneNode: no template found for %s\n", contextNode->name));
        }
#endif
	oldNode = ctxt->node;
	ctxt->node = contextNode;
	xsltDefaultProcessOneNode(ctxt, contextNode, withParams);
	ctxt->node = oldNode;
	return;
    }

    if (contextNode->type == XML_ATTRIBUTE_NODE) {
	xsltTemplatePtr oldCurTempRule = ctxt->currentTemplateRule;
	/*
	* Set the "current template rule".
	*/
	ctxt->currentTemplateRule = templ;

#ifdef WITH_XSLT_DEBUG_PROCESS
	XSLT_TRACE(ctxt,XSLT_TRACE_PROCESS_NODE,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltProcessOneNode: applying template '%s' for attribute %s\n",
	                 templ->match, contextNode->name));
#endif
	xsltApplyXSLTTemplate(ctxt, contextNode, templ->content, templ, withParams);

	ctxt->currentTemplateRule = oldCurTempRule;
    } else {
	xsltTemplatePtr oldCurTempRule = ctxt->currentTemplateRule;
	/*
	* Set the "current template rule".
	*/
	ctxt->currentTemplateRule = templ;

#ifdef WITH_XSLT_DEBUG_PROCESS
	if (contextNode->type == XML_DOCUMENT_NODE) {
	    XSLT_TRACE(ctxt,XSLT_TRACE_PROCESS_NODE,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltProcessOneNode: applying template '%s' for /\n",
	                     templ->match));
	} else {
	    XSLT_TRACE(ctxt,XSLT_TRACE_PROCESS_NODE,xsltGenericDebug(xsltGenericDebugContext,
	     "xsltProcessOneNode: applying template '%s' for %s\n",
	                     templ->match, contextNode->name));
        }
#endif
	xsltApplyXSLTTemplate(ctxt, contextNode, templ->content, templ, withParams);

	ctxt->currentTemplateRule = oldCurTempRule;
    }
}