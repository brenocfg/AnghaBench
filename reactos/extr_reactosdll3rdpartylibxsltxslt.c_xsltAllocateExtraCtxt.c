#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xsltTransformContextPtr ;
typedef  TYPE_3__* xsltRuntimeExtraPtr ;
typedef  int /*<<< orphan*/  xsltRuntimeExtra ;
struct TYPE_7__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_9__ {TYPE_1__ val; int /*<<< orphan*/ * deallocate; int /*<<< orphan*/ * info; } ;
struct TYPE_8__ {int extrasNr; int extrasMax; TYPE_3__* extras; } ;

/* Variables and functions */
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlRealloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  xsltTransformError (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int
xsltAllocateExtraCtxt(xsltTransformContextPtr ctxt)
{
    if (ctxt->extrasNr >= ctxt->extrasMax) {
	int i;
	if (ctxt->extrasNr == 0) {
	    ctxt->extrasMax = 20;
	    ctxt->extras = (xsltRuntimeExtraPtr)
		xmlMalloc(ctxt->extrasMax * sizeof(xsltRuntimeExtra));
	    if (ctxt->extras == NULL) {
		xsltTransformError(ctxt, NULL, NULL,
			"xsltAllocateExtraCtxt: out of memory\n");
		return(0);
	    }
	    for (i = 0;i < ctxt->extrasMax;i++) {
		ctxt->extras[i].info = NULL;
		ctxt->extras[i].deallocate = NULL;
		ctxt->extras[i].val.ptr = NULL;
	    }

	} else {
	    xsltRuntimeExtraPtr tmp;

	    ctxt->extrasMax += 100;
	    tmp = (xsltRuntimeExtraPtr) xmlRealloc(ctxt->extras,
		            ctxt->extrasMax * sizeof(xsltRuntimeExtra));
	    if (tmp == NULL) {
		xsltTransformError(ctxt, NULL, NULL,
			"xsltAllocateExtraCtxt: out of memory\n");
		return(0);
	    }
	    ctxt->extras = tmp;
	    for (i = ctxt->extrasNr;i < ctxt->extrasMax;i++) {
		ctxt->extras[i].info = NULL;
		ctxt->extras[i].deallocate = NULL;
		ctxt->extras[i].val.ptr = NULL;
	    }
	}
    }
    return(ctxt->extrasNr++);
}