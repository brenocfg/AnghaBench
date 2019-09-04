#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  TYPE_3__* xsltStackElemPtr ;
typedef  TYPE_4__* xmlXPathObjectPtr ;
typedef  TYPE_5__* xmlXPathContextPtr ;
typedef  int /*<<< orphan*/ * xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/  xmlNsPtr ;
typedef  void* xmlNodePtr ;
typedef  TYPE_6__* xmlDocPtr ;
struct TYPE_26__ {int /*<<< orphan*/  psvi; } ;
struct TYPE_25__ {int proximityPosition; int contextSize; int nsNr; int /*<<< orphan*/ * namespaces; TYPE_15__* node; TYPE_6__* doc; } ;
struct TYPE_24__ {scalar_t__ boolval; } ;
struct TYPE_23__ {int /*<<< orphan*/ * tree; TYPE_6__* fragment; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * select; } ;
struct TYPE_22__ {int nsNr; int /*<<< orphan*/ * inst; int /*<<< orphan*/ * comp; int /*<<< orphan*/ * nsList; } ;
struct TYPE_21__ {void* inst; TYPE_6__* output; void* insert; TYPE_3__* contextVariable; TYPE_15__* node; int /*<<< orphan*/  state; TYPE_5__* xpathCtxt; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_6__* doc; } ;

/* Variables and functions */
 scalar_t__ XML_NAMESPACE_DECL ; 
 int /*<<< orphan*/  XSLT_RVT_LOCAL ; 
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  XSLT_VAR_IN_SELECT ; 
 int /*<<< orphan*/ * xmlXPathCompile (int /*<<< orphan*/ *) ; 
 TYPE_4__* xmlXPathCompiledEval (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ *) ; 
 TYPE_4__* xmlXPathNewCString (char*) ; 
 TYPE_4__* xmlXPathNewValueTree (void*) ; 
 int /*<<< orphan*/  xsltApplyOneTemplate (TYPE_1__*,TYPE_15__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* xsltCreateRVT (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xmlXPathObjectPtr
xsltEvalVariable(xsltTransformContextPtr ctxt, xsltStackElemPtr variable,
	         xsltStylePreCompPtr castedComp)
{
#ifdef XSLT_REFACTORED
    xsltStyleItemVariablePtr comp =
	(xsltStyleItemVariablePtr) castedComp;
#else
    xsltStylePreCompPtr comp = castedComp;
#endif
    xmlXPathObjectPtr result = NULL;
    xmlNodePtr oldInst;

    if ((ctxt == NULL) || (variable == NULL))
	return(NULL);

    /*
    * A variable or parameter are evaluated on demand; thus the
    * context (of XSLT and XPath) need to be temporarily adjusted and
    * restored on exit.
    */
    oldInst = ctxt->inst;

#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
	"Evaluating variable '%s'\n", variable->name));
#endif
    if (variable->select != NULL) {
	xmlXPathCompExprPtr xpExpr = NULL;
	xmlDocPtr oldXPDoc;
	xmlNodePtr oldXPContextNode;
	int oldXPProximityPosition, oldXPContextSize, oldXPNsNr;
	xmlNsPtr *oldXPNamespaces;
	xmlXPathContextPtr xpctxt = ctxt->xpathCtxt;
	xsltStackElemPtr oldVar = ctxt->contextVariable;

	if ((comp != NULL) && (comp->comp != NULL)) {
	    xpExpr = comp->comp;
	} else {
	    xpExpr = xmlXPathCompile(variable->select);
	}
	if (xpExpr == NULL)
	    return(NULL);
	/*
	* Save context states.
	*/
	oldXPDoc = xpctxt->doc;
	oldXPContextNode = xpctxt->node;
	oldXPProximityPosition = xpctxt->proximityPosition;
	oldXPContextSize = xpctxt->contextSize;
	oldXPNamespaces = xpctxt->namespaces;
	oldXPNsNr = xpctxt->nsNr;

	xpctxt->node = ctxt->node;
	/*
	* OPTIMIZE TODO: Lame try to set the context doc.
	*   Get rid of this somehow in xpath.c.
	*/
	if ((ctxt->node->type != XML_NAMESPACE_DECL) &&
	    ctxt->node->doc)
	    xpctxt->doc = ctxt->node->doc;
	/*
	* BUG TODO: The proximity position and the context size will
	*  potentially be wrong.
	*  Example:
	*  <xsl:template select="foo">
	*    <xsl:variable name="pos" select="position()"/>
	*    <xsl:for-each select="bar">
	*      <xsl:value-of select="$pos"/>
	*    </xsl:for-each>
	*  </xsl:template>
	*  Here the proximity position and context size are changed
	*  to the context of <xsl:for-each select="bar">, but
	*  the variable needs to be evaluated in the context of
	*  <xsl:template select="foo">.
	*/
	if (comp != NULL) {

#ifdef XSLT_REFACTORED
	    if (comp->inScopeNs != NULL) {
		xpctxt->namespaces = comp->inScopeNs->list;
		xpctxt->nsNr = comp->inScopeNs->xpathNumber;
	    } else {
		xpctxt->namespaces = NULL;
		xpctxt->nsNr = 0;
	    }
#else
	    xpctxt->namespaces = comp->nsList;
	    xpctxt->nsNr = comp->nsNr;
#endif
	} else {
	    xpctxt->namespaces = NULL;
	    xpctxt->nsNr = 0;
	}

	/*
	* We need to mark that we are "selecting" a var's value;
	* if any tree fragments are created inside the expression,
	* then those need to be stored inside the variable; otherwise
	* we'll eventually free still referenced fragments, before
	* we leave the scope of the variable.
	*/
	ctxt->contextVariable = variable;
	variable->flags |= XSLT_VAR_IN_SELECT;

	result = xmlXPathCompiledEval(xpExpr, xpctxt);

	variable->flags ^= XSLT_VAR_IN_SELECT;
	/*
	* Restore Context states.
	*/
	ctxt->contextVariable = oldVar;

	xpctxt->doc = oldXPDoc;
	xpctxt->node = oldXPContextNode;
	xpctxt->contextSize = oldXPContextSize;
	xpctxt->proximityPosition = oldXPProximityPosition;
	xpctxt->namespaces = oldXPNamespaces;
	xpctxt->nsNr = oldXPNsNr;

	if ((comp == NULL) || (comp->comp == NULL))
	    xmlXPathFreeCompExpr(xpExpr);
	if (result == NULL) {
	    xsltTransformError(ctxt, NULL,
		(comp != NULL) ? comp->inst : NULL,
		"Failed to evaluate the expression of variable '%s'.\n",
		variable->name);
	    ctxt->state = XSLT_STATE_STOPPED;

#ifdef WITH_XSLT_DEBUG_VARIABLE
#ifdef LIBXML_DEBUG_ENABLED
	} else {
	    if ((xsltGenericDebugContext == stdout) ||
		(xsltGenericDebugContext == stderr))
		xmlXPathDebugDumpObject((FILE *)xsltGenericDebugContext,
					result, 0);
#endif
#endif
	}
    } else {
	if (variable->tree == NULL) {
	    result = xmlXPathNewCString("");
	} else {
	    if (variable->tree) {
		xmlDocPtr container;
		xmlNodePtr oldInsert;
		xmlDocPtr  oldOutput;
		xsltStackElemPtr oldVar = ctxt->contextVariable;

		/*
		* Generate a result tree fragment.
		*/
		container = xsltCreateRVT(ctxt);
		if (container == NULL)
		    goto error;
		/*
		* NOTE: Local Result Tree Fragments of params/variables
		* are not registered globally anymore; the life-time
		* is not directly dependant of the param/variable itself.
		*
		* OLD: xsltRegisterTmpRVT(ctxt, container);
		*/
		/*
		* Attach the Result Tree Fragment to the variable;
		* when the variable is freed, it will also free
		* the Result Tree Fragment.
		*/
		variable->fragment = container;
                container->psvi = XSLT_RVT_LOCAL;

		oldOutput = ctxt->output;
		oldInsert = ctxt->insert;

		ctxt->output = container;
		ctxt->insert = (xmlNodePtr) container;
		ctxt->contextVariable = variable;
		/*
		* Process the sequence constructor (variable->tree).
		* The resulting tree will be held by @container.
		*/
		xsltApplyOneTemplate(ctxt, ctxt->node, variable->tree,
		    NULL, NULL);

		ctxt->contextVariable = oldVar;
		ctxt->insert = oldInsert;
		ctxt->output = oldOutput;

		result = xmlXPathNewValueTree((xmlNodePtr) container);
	    }
	    if (result == NULL) {
		result = xmlXPathNewCString("");
	    } else {
		/*
		* Freeing is not handled there anymore.
		* QUESTION TODO: What does the above comment mean?
		*/
	        result->boolval = 0;
	    }
#ifdef WITH_XSLT_DEBUG_VARIABLE
#ifdef LIBXML_DEBUG_ENABLED

	    if ((xsltGenericDebugContext == stdout) ||
		(xsltGenericDebugContext == stderr))
		xmlXPathDebugDumpObject((FILE *)xsltGenericDebugContext,
					result, 0);
#endif
#endif
	}
    }

error:
    ctxt->inst = oldInst;
    return(result);
}