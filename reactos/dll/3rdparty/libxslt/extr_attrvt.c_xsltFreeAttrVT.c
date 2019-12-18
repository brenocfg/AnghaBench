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
typedef  TYPE_1__* xsltAttrVTPtr ;
typedef  int /*<<< orphan*/  xmlXPathCompExprPtr ;
struct TYPE_5__ {int strstart; int nb_seg; struct TYPE_5__* nsList; int /*<<< orphan*/ ** segments; } ;
typedef  TYPE_1__ xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xsltFreeAttrVT(xsltAttrVTPtr avt) {
    int i;

    if (avt == NULL) return;

    if (avt->strstart == 1) {
	for (i = 0;i < avt->nb_seg; i += 2)
	    if (avt->segments[i] != NULL)
		xmlFree((xmlChar *) avt->segments[i]);
	for (i = 1;i < avt->nb_seg; i += 2)
	    xmlXPathFreeCompExpr((xmlXPathCompExprPtr) avt->segments[i]);
    } else {
	for (i = 0;i < avt->nb_seg; i += 2)
	    xmlXPathFreeCompExpr((xmlXPathCompExprPtr) avt->segments[i]);
	for (i = 1;i < avt->nb_seg; i += 2)
	    if (avt->segments[i] != NULL)
		xmlFree((xmlChar *) avt->segments[i]);
    }
    if (avt->nsList != NULL)
        xmlFree(avt->nsList);
    xmlFree(avt);
}