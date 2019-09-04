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
struct TYPE_3__ {int exclPrefixMax; int exclPrefixNr; int /*<<< orphan*/ * exclPrefix; int /*<<< orphan*/ ** exclPrefixTab; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlRealloc (int /*<<< orphan*/ **,int) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
exclPrefixPush(xsltStylesheetPtr style, xmlChar * value)
{
    int i;

    if (style->exclPrefixMax == 0) {
        style->exclPrefixMax = 4;
        style->exclPrefixTab =
            (xmlChar * *)xmlMalloc(style->exclPrefixMax *
                                   sizeof(style->exclPrefixTab[0]));
        if (style->exclPrefixTab == NULL) {
            xmlGenericError(xmlGenericErrorContext, "malloc failed !\n");
            return (-1);
        }
    }
    /* do not push duplicates */
    for (i = 0;i < style->exclPrefixNr;i++) {
        if (xmlStrEqual(style->exclPrefixTab[i], value))
	    return(-1);
    }
    if (style->exclPrefixNr >= style->exclPrefixMax) {
        style->exclPrefixMax *= 2;
        style->exclPrefixTab =
            (xmlChar * *)xmlRealloc(style->exclPrefixTab,
                                    style->exclPrefixMax *
                                    sizeof(style->exclPrefixTab[0]));
        if (style->exclPrefixTab == NULL) {
            xmlGenericError(xmlGenericErrorContext, "realloc failed !\n");
            return (-1);
        }
    }
    style->exclPrefixTab[style->exclPrefixNr] = value;
    style->exclPrefix = value;
    return (style->exclPrefixNr++);
}