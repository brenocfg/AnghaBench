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
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltTemplatePtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
struct TYPE_9__ {int /*<<< orphan*/ * elem; } ;
struct TYPE_8__ {int debugStatus; int /*<<< orphan*/ * inst; } ;

/* Variables and functions */
 int XSLT_DEBUG_NONE ; 
#define  XSLT_DEBUG_QUIT 129 
#define  XSLT_DEBUG_RUN_RESTART 128 
 int xslAddCall (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xslDropCall () ; 
 int /*<<< orphan*/  xslHandleDebugger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static xmlNodePtr
xsltDebuggerStartSequenceConstructor(xsltTransformContextPtr ctxt,
				     xmlNodePtr contextNode,
				     xmlNodePtr list,
				     xsltTemplatePtr templ,
				     int *addCallResult)
{
    xmlNodePtr debugedNode = NULL;

    if (ctxt->debugStatus != XSLT_DEBUG_NONE) {
        if (templ) {
            *addCallResult = xslAddCall(templ, templ->elem);
        } else {
            *addCallResult = xslAddCall(NULL, list);
        }
        switch (ctxt->debugStatus) {
            case XSLT_DEBUG_RUN_RESTART:
            case XSLT_DEBUG_QUIT:
                if (*addCallResult)
                    xslDropCall();
                return(NULL);
        }
        if (templ) {
            xslHandleDebugger(templ->elem, contextNode, templ, ctxt);
            debugedNode = templ->elem;
        } else if (list) {
            xslHandleDebugger(list, contextNode, templ, ctxt);
            debugedNode = list;
        } else if (ctxt->inst) {
            xslHandleDebugger(ctxt->inst, contextNode, templ, ctxt);
            debugedNode = ctxt->inst;
        }
    }
    return(debugedNode);
}