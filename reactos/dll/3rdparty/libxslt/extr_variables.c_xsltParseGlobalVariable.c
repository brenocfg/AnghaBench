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
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xsltStylesheetPtr ;
typedef  TYPE_1__* xsltStylePreCompPtr ;
typedef  TYPE_1__* xsltStyleItemVariablePtr ;
typedef  TYPE_3__* xmlNodePtr ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/ * children; scalar_t__ psvi; } ;
struct TYPE_9__ {int /*<<< orphan*/  select; int /*<<< orphan*/  ns; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 int /*<<< orphan*/  XSLT_CCTXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltParseSequenceConstructor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltParseTemplateContent (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  xsltRegisterGlobalVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltStylePreCompute (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  xsltTransformError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,char*) ; 

void
xsltParseGlobalVariable(xsltStylesheetPtr style, xmlNodePtr cur)
{
#ifdef XSLT_REFACTORED
    xsltStyleItemVariablePtr comp;
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
    comp = (xsltStyleItemVariablePtr) cur->psvi;
#else
    xsltStylePreCompute(style, cur);
    comp = (xsltStylePreCompPtr) cur->psvi;
#endif
    if (comp == NULL) {
	xsltTransformError(NULL, style, cur,
	     "xsl:variable : compilation failed\n");
	return;
    }

    if (comp->name == NULL) {
	xsltTransformError(NULL, style, cur,
	    "xsl:variable : missing name attribute\n");
	return;
    }

    /*
    * Parse the content (a sequence constructor) of xsl:variable.
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
	"Registering global variable %s\n", comp->name);
#endif

    xsltRegisterGlobalVariable(style, comp->name, comp->ns,
	comp->select, cur->children, (xsltStylePreCompPtr) comp,
	NULL);
}