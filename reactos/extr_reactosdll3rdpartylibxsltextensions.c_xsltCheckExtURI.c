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
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltExtDefPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  URI; } ;
struct TYPE_4__ {int /*<<< orphan*/ * nsDefs; } ;

/* Variables and functions */
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int
xsltCheckExtURI(xsltStylesheetPtr style, const xmlChar * URI)
{
    xsltExtDefPtr cur;

    if ((style == NULL) || (style->nsDefs == NULL))
        return (0);
    if (URI == NULL)
        return (0);
    cur = (xsltExtDefPtr) style->nsDefs;
    while (cur != NULL) {
        if (xmlStrEqual(URI, cur->URI))
            return (1);
        cur = cur->next;
    }
    return (0);
}