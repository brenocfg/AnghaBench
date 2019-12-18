#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltTransformContextPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
struct TYPE_5__ {int /*<<< orphan*/  (* sortfunc ) (TYPE_1__*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xsltSortFunction (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void
xsltDoSortFunction(xsltTransformContextPtr ctxt, xmlNodePtr * sorts,
                   int nbsorts)
{
    if (ctxt->sortfunc != NULL)
	(ctxt->sortfunc)(ctxt, sorts, nbsorts);
    else if (xsltSortFunction != NULL)
        xsltSortFunction(ctxt, sorts, nbsorts);
}