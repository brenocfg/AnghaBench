#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltStylesheetPtr ;
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  TYPE_2__* xmlNodePtr ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/ * children; scalar_t__ psvi; } ;
struct TYPE_8__ {int /*<<< orphan*/  select; int /*<<< orphan*/  ns; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  xsltParseTemplateContent (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltRegisterGlobalVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltStylePreCompute (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,char*) ; 

void
xsltParseGlobalParam(xsltStylesheetPtr style, xmlNodePtr cur) {
#ifdef XSLT_REFACTORED
    xsltStyleItemParamPtr comp;
#else
    xsltStylePreCompPtr comp;
#endif

    if ((cur == NULL) || (style == NULL) || (cur->type != XML_ELEMENT_NODE))
	return;

#ifdef XSLT_REFACTORED
    /*
    * Note that xsltStylePreCompute() will be called from
    * xslt.c only.
    */
    comp = (xsltStyleItemParamPtr) cur->psvi;
#else
    xsltStylePreCompute(style, cur);
    comp = (xsltStylePreCompPtr) cur->psvi;
#endif
    if (comp == NULL) {
	xsltTransformError(NULL, style, cur,
	     "xsl:param : compilation failed\n");
	return;
    }

    if (comp->name == NULL) {
	xsltTransformError(NULL, style, cur,
	    "xsl:param : missing name attribute\n");
	return;
    }

    /*
    * Parse the content (a sequence constructor) of xsl:param.
    */
    if (cur->children != NULL) {
#ifdef XSLT_REFACTORED
        xsltParseSequenceConstructor(XSLT_CCTXT(style), cur->children);
#else
        xsltParseTemplateContent(style, cur);
#endif
    }

#ifdef WITH_XSLT_DEBUG_VARIABLE
    xsltGenericDebug(xsltGenericDebugContext,
	"Registering global param %s\n", comp->name);
#endif

    xsltRegisterGlobalVariable(style, comp->name, comp->ns,
	comp->select, cur->children, (xsltStylePreCompPtr) comp,
	NULL);
}