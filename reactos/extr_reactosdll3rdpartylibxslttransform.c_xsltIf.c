#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStylePreCompPtr ;
typedef  int /*<<< orphan*/  xsltElemPreCompPtr ;
typedef  TYPE_3__* xmlXPathObjectPtr ;
typedef  TYPE_4__* xmlNodePtr ;
struct TYPE_22__ {int /*<<< orphan*/  children; } ;
struct TYPE_21__ {scalar_t__ type; int boolval; } ;
struct TYPE_20__ {int /*<<< orphan*/ * comp; int /*<<< orphan*/ * test; } ;
struct TYPE_19__ {void* state; } ;

/* Variables and functions */
 scalar_t__ XPATH_BOOLEAN ; 
 void* XSLT_STATE_STOPPED ; 
 TYPE_3__* xmlXPathConvertBoolean (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlXPathFreeObject (TYPE_3__*) ; 
 int /*<<< orphan*/  xsltApplySequenceConstructor (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* xsltPreCompEval (TYPE_1__*,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*,char*) ; 

void
xsltIf(xsltTransformContextPtr ctxt, xmlNodePtr contextNode,
	           xmlNodePtr inst, xsltElemPreCompPtr castedComp)
{
    int res = 0;

#ifdef XSLT_REFACTORED
    xsltStyleItemIfPtr comp = (xsltStyleItemIfPtr) castedComp;
#else
    xsltStylePreCompPtr comp = (xsltStylePreCompPtr) castedComp;
#endif

    if ((ctxt == NULL) || (contextNode == NULL) || (inst == NULL))
	return;
    if ((comp == NULL) || (comp->test == NULL) || (comp->comp == NULL)) {
	xsltTransformError(ctxt, NULL, inst,
	    "Internal error in xsltIf(): "
	    "The XSLT 'if' instruction was not compiled.\n");
	return;
    }

#ifdef WITH_XSLT_DEBUG_PROCESS
    XSLT_TRACE(ctxt,XSLT_TRACE_IF,xsltGenericDebug(xsltGenericDebugContext,
	 "xsltIf: test %s\n", comp->test));
#endif

#ifdef XSLT_FAST_IF
    {
	xmlDocPtr oldLocalFragmentTop = ctxt->localRVT;

	res = xsltPreCompEvalToBoolean(ctxt, contextNode, comp);

	/*
	* Cleanup fragments created during evaluation of the
	* "select" expression.
	*/
	if (oldLocalFragmentTop != ctxt->localRVT)
	    xsltReleaseLocalRVTs(ctxt, oldLocalFragmentTop);
    }

#ifdef WITH_XSLT_DEBUG_PROCESS
    XSLT_TRACE(ctxt,XSLT_TRACE_IF,xsltGenericDebug(xsltGenericDebugContext,
	"xsltIf: test evaluate to %d\n", res));
#endif

    if (res == -1) {
	ctxt->state = XSLT_STATE_STOPPED;
	goto error;
    }
    if (res == 1) {
	/*
	* Instantiate the sequence constructor of xsl:if.
	*/
	xsltApplySequenceConstructor(ctxt,
	    contextNode, inst->children, NULL);
    }

#else /* XSLT_FAST_IF */
    {
	/*
	* OLD CODE:
	*/
	xmlXPathObjectPtr xpobj = xsltPreCompEval(ctxt, contextNode, comp);
	if (xpobj != NULL) {
	    if (xpobj->type != XPATH_BOOLEAN)
		xpobj = xmlXPathConvertBoolean(xpobj);
	    if (xpobj->type == XPATH_BOOLEAN) {
		res = xpobj->boolval;

#ifdef WITH_XSLT_DEBUG_PROCESS
		XSLT_TRACE(ctxt,XSLT_TRACE_IF,xsltGenericDebug(xsltGenericDebugContext,
		    "xsltIf: test evaluate to %d\n", res));
#endif
		if (res) {
		    xsltApplySequenceConstructor(ctxt,
			contextNode, inst->children, NULL);
		}
	    } else {

#ifdef WITH_XSLT_DEBUG_PROCESS
		XSLT_TRACE(ctxt, XSLT_TRACE_IF,
		    xsltGenericDebug(xsltGenericDebugContext,
		    "xsltIf: test didn't evaluate to a boolean\n"));
#endif
		ctxt->state = XSLT_STATE_STOPPED;
	    }
	    xmlXPathFreeObject(xpobj);
	} else {
	    ctxt->state = XSLT_STATE_STOPPED;
	}
    }
#endif /* else of XSLT_FAST_IF */

error:
    return;
}