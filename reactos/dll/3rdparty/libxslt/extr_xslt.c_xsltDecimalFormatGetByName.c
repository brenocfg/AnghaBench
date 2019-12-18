#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  TYPE_2__* xsltDecimalFormatPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * nsUri; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_2__* decimalFormat; } ;

/* Variables and functions */
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* xsltNextImport (TYPE_1__*) ; 

xsltDecimalFormatPtr
xsltDecimalFormatGetByName(xsltStylesheetPtr style, xmlChar *name)
{
    xsltDecimalFormatPtr result = NULL;

    if (name == NULL)
	return style->decimalFormat;

    while (style != NULL) {
	for (result = style->decimalFormat->next;
	     result != NULL;
	     result = result->next) {
	    if ((result->nsUri == NULL) && xmlStrEqual(name, result->name))
		return result;
	}
	style = xsltNextImport(style);
    }
    return result;
}