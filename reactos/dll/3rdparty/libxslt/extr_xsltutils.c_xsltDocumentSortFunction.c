#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodeSetPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
struct TYPE_3__ {int nodeNr; int /*<<< orphan*/ * nodeTab; } ;

/* Variables and functions */
 int xmlXPathCmpNodes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xsltDocumentSortFunction(xmlNodeSetPtr list) {
    int i, j;
    int len, tst;
    xmlNodePtr node;

    if (list == NULL)
	return;
    len = list->nodeNr;
    if (len <= 1)
	return;
    /* TODO: sort is really not optimized, does it needs to ? */
    for (i = 0;i < len -1;i++) {
	for (j = i + 1; j < len; j++) {
	    tst = xmlXPathCmpNodes(list->nodeTab[i], list->nodeTab[j]);
	    if (tst == -1) {
		node = list->nodeTab[i];
		list->nodeTab[i] = list->nodeTab[j];
		list->nodeTab[j] = node;
	    }
	}
    }
}