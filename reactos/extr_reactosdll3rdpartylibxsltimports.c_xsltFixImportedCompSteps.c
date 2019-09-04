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
typedef  TYPE_1__* xsltStylesheetPtr ;
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* imports; scalar_t__ extrasNr; int /*<<< orphan*/  templatesHash; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlHashScan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xsltNormalizeCompSteps ; 

__attribute__((used)) static void xsltFixImportedCompSteps(xsltStylesheetPtr master,
			xsltStylesheetPtr style) {
    xsltStylesheetPtr res;
    xmlHashScan(style->templatesHash, xsltNormalizeCompSteps, master);
    master->extrasNr += style->extrasNr;
    for (res = style->imports; res != NULL; res = res->next) {
        xsltFixImportedCompSteps(master, res);
    }
}