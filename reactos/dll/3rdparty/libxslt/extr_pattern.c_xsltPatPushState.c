#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
struct TYPE_12__ {int maxstates; int nbstates; TYPE_3__* states; } ;
typedef  TYPE_2__ xsltStepStates ;
typedef  TYPE_3__* xsltStepStatePtr ;
struct TYPE_13__ {int step; TYPE_5__* node; } ;
typedef  TYPE_3__ xsltStepState ;
typedef  TYPE_5__* xmlNodePtr ;
struct TYPE_14__ {char* name; } ;
struct TYPE_11__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_STATE_STOPPED ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_3__* xmlMalloc (int) ; 
 scalar_t__ xmlRealloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xsltGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericErrorContext ; 

__attribute__((used)) static int
xsltPatPushState(xsltTransformContextPtr ctxt, xsltStepStates *states,
                 int step, xmlNodePtr node) {
    if ((states->states == NULL) || (states->maxstates <= 0)) {
        states->maxstates = 4;
	states->nbstates = 0;
	states->states = xmlMalloc(4 * sizeof(xsltStepState));
    }
    else if (states->maxstates <= states->nbstates) {
        xsltStepState *tmp;

	tmp = (xsltStepStatePtr) xmlRealloc(states->states,
			       2 * states->maxstates * sizeof(xsltStepState));
	if (tmp == NULL) {
	    xsltGenericError(xsltGenericErrorContext,
	     "xsltPatPushState: memory re-allocation failure.\n");
	    ctxt->state = XSLT_STATE_STOPPED;
	    return(-1);
	}
	states->states = tmp;
	states->maxstates *= 2;
    }
    states->states[states->nbstates].step = step;
    states->states[states->nbstates++].node = node;
#if 0
    fprintf(stderr, "Push: %d, %s\n", step, node->name);
#endif
    return(0);
}