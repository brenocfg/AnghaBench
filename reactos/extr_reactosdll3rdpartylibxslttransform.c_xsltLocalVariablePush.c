#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  TYPE_2__* xsltStackElemPtr ;
struct TYPE_7__ {int level; } ;
struct TYPE_6__ {int varsMax; int varsNr; TYPE_2__* vars; TYPE_2__** varsTab; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlRealloc (TYPE_2__**,int) ; 

int
xsltLocalVariablePush(xsltTransformContextPtr ctxt,
		      xsltStackElemPtr variable,
		      int level)
{
    if (ctxt->varsMax == 0) {
	ctxt->varsMax = 10;
	ctxt->varsTab =
	    (xsltStackElemPtr *) xmlMalloc(ctxt->varsMax *
	    sizeof(ctxt->varsTab[0]));
	if (ctxt->varsTab == NULL) {
	    xmlGenericError(xmlGenericErrorContext, "malloc failed !\n");
	    return (-1);
	}
    }
    if (ctxt->varsNr >= ctxt->varsMax) {
	ctxt->varsMax *= 2;
	ctxt->varsTab =
	    (xsltStackElemPtr *) xmlRealloc(ctxt->varsTab,
	    ctxt->varsMax *
	    sizeof(ctxt->varsTab[0]));
	if (ctxt->varsTab == NULL) {
	    xmlGenericError(xmlGenericErrorContext, "realloc failed !\n");
	    return (-1);
	}
    }
    ctxt->varsTab[ctxt->varsNr++] = variable;
    ctxt->vars = variable;
    variable->level = level;
    return(0);
}