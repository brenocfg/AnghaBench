#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltTransformFunction ;
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltElemPreCompPtr ;
typedef  int /*<<< orphan*/  xsltElemPreCompDeallocator ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  free; int /*<<< orphan*/  inst; int /*<<< orphan*/  func; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_2__* preComps; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_FUNC_EXTENSION ; 

void
xsltInitElemPreComp(xsltElemPreCompPtr comp, xsltStylesheetPtr style,
                    xmlNodePtr inst, xsltTransformFunction function,
                    xsltElemPreCompDeallocator freeFunc)
{
    comp->type = XSLT_FUNC_EXTENSION;
    comp->func = function;
    comp->inst = inst;
    comp->free = freeFunc;

    comp->next = style->preComps;
    style->preComps = comp;
}