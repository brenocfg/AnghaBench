#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStepOpPtr ;
typedef  TYPE_1__* xsltCompMatchPtr ;
typedef  int /*<<< orphan*/  xsltCompMatch ;
struct TYPE_7__ {int nbStep; struct TYPE_7__* steps; int /*<<< orphan*/ * comp; struct TYPE_7__* value3; struct TYPE_7__* value2; struct TYPE_7__* value; struct TYPE_7__* nsList; int /*<<< orphan*/ * pattern; } ;
typedef  TYPE_1__ xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xsltFreeCompMatch(xsltCompMatchPtr comp) {
    xsltStepOpPtr op;
    int i;

    if (comp == NULL)
	return;
    if (comp->pattern != NULL)
	xmlFree((xmlChar *)comp->pattern);
    if (comp->nsList != NULL)
	xmlFree(comp->nsList);
    for (i = 0;i < comp->nbStep;i++) {
	op = &comp->steps[i];
	if (op->value != NULL)
	    xmlFree(op->value);
	if (op->value2 != NULL)
	    xmlFree(op->value2);
	if (op->value3 != NULL)
	    xmlFree(op->value3);
	if (op->comp != NULL)
	    xmlXPathFreeCompExpr(op->comp);
    }
    xmlFree(comp->steps);
    memset(comp, -1, sizeof(xsltCompMatch));
    xmlFree(comp);
}