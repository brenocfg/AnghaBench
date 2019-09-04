#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsltOp ;
typedef  TYPE_2__* xsltCompMatchPtr ;
typedef  int /*<<< orphan*/  xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {int nbStep; TYPE_1__* steps; } ;
struct TYPE_4__ {int previousExtra; int indexExtra; int lenExtra; int /*<<< orphan*/  comp; int /*<<< orphan*/  op; int /*<<< orphan*/ * value3; int /*<<< orphan*/ * value2; int /*<<< orphan*/ * value; } ;

/* Variables and functions */

__attribute__((used)) static void
xsltSwapTopCompMatch(xsltCompMatchPtr comp) {
    int i;
    int j = comp->nbStep - 1;

    if (j > 0) {
	register xmlChar *tmp;
	register xsltOp op;
	register xmlXPathCompExprPtr expr;
	register int t;
	i = j - 1;
	tmp = comp->steps[i].value;
	comp->steps[i].value = comp->steps[j].value;
	comp->steps[j].value = tmp;
	tmp = comp->steps[i].value2;
	comp->steps[i].value2 = comp->steps[j].value2;
	comp->steps[j].value2 = tmp;
	tmp = comp->steps[i].value3;
	comp->steps[i].value3 = comp->steps[j].value3;
	comp->steps[j].value3 = tmp;
	op = comp->steps[i].op;
	comp->steps[i].op = comp->steps[j].op;
	comp->steps[j].op = op;
	expr = comp->steps[i].comp;
	comp->steps[i].comp = comp->steps[j].comp;
	comp->steps[j].comp = expr;
	t = comp->steps[i].previousExtra;
	comp->steps[i].previousExtra = comp->steps[j].previousExtra;
	comp->steps[j].previousExtra = t;
	t = comp->steps[i].indexExtra;
	comp->steps[i].indexExtra = comp->steps[j].indexExtra;
	comp->steps[j].indexExtra = t;
	t = comp->steps[i].lenExtra;
	comp->steps[i].lenExtra = comp->steps[j].lenExtra;
	comp->steps[j].lenExtra = t;
    }
}