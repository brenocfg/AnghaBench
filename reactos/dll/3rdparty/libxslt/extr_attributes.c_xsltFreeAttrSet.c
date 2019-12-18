#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltAttrSetPtr ;
struct TYPE_4__ {int /*<<< orphan*/  useAttrSets; int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeAttrElemList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltFreeUseAttrSetList (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xsltFreeAttrSet(xsltAttrSetPtr set) {
    if (set == NULL)
        return;

    xsltFreeAttrElemList(set->attrs);
    xsltFreeUseAttrSetList(set->useAttrSets);
    xmlFree(set);
}