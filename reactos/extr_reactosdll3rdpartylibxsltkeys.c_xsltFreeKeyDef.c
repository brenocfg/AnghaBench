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
typedef  TYPE_1__* xsltKeyDefPtr ;
typedef  int /*<<< orphan*/  xsltKeyDef ;
struct TYPE_5__ {struct TYPE_5__* nsList; struct TYPE_5__* use; struct TYPE_5__* match; struct TYPE_5__* nameURI; struct TYPE_5__* name; int /*<<< orphan*/ * usecomp; int /*<<< orphan*/ * comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xsltFreeKeyDef(xsltKeyDefPtr keyd) {
    if (keyd == NULL)
	return;
    if (keyd->comp != NULL)
	xmlXPathFreeCompExpr(keyd->comp);
    if (keyd->usecomp != NULL)
	xmlXPathFreeCompExpr(keyd->usecomp);
    if (keyd->name != NULL)
	xmlFree(keyd->name);
    if (keyd->nameURI != NULL)
	xmlFree(keyd->nameURI);
    if (keyd->match != NULL)
	xmlFree(keyd->match);
    if (keyd->use != NULL)
	xmlFree(keyd->use);
    if (keyd->nsList != NULL)
        xmlFree(keyd->nsList);
    memset(keyd, -1, sizeof(xsltKeyDef));
    xmlFree(keyd);
}