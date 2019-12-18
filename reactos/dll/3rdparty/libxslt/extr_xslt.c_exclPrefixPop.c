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
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_3__ {int exclPrefixNr; int /*<<< orphan*/ ** exclPrefixTab; int /*<<< orphan*/ * exclPrefix; } ;

/* Variables and functions */

__attribute__((used)) static xmlChar *
exclPrefixPop(xsltStylesheetPtr style)
{
    xmlChar *ret;

    if (style->exclPrefixNr <= 0)
        return (0);
    style->exclPrefixNr--;
    if (style->exclPrefixNr > 0)
        style->exclPrefix = style->exclPrefixTab[style->exclPrefixNr - 1];
    else
        style->exclPrefix = NULL;
    ret = style->exclPrefixTab[style->exclPrefixNr];
    style->exclPrefixTab[style->exclPrefixNr] = 0;
    return (ret);
}