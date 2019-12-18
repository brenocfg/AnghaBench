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
typedef  TYPE_1__* xsltDecimalFormatPtr ;
struct TYPE_4__ {struct TYPE_4__* name; struct TYPE_4__* noNumber; struct TYPE_4__* infinity; struct TYPE_4__* minusSign; struct TYPE_4__* zeroDigit; struct TYPE_4__* permille; struct TYPE_4__* percent; struct TYPE_4__* grouping; struct TYPE_4__* decimalPoint; struct TYPE_4__* patternSeparator; struct TYPE_4__* digit; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 

__attribute__((used)) static void
xsltFreeDecimalFormat(xsltDecimalFormatPtr self)
{
    if (self != NULL) {
	if (self->digit)
	    xmlFree(self->digit);
	if (self->patternSeparator)
	    xmlFree(self->patternSeparator);
	if (self->decimalPoint)
	    xmlFree(self->decimalPoint);
	if (self->grouping)
	    xmlFree(self->grouping);
	if (self->percent)
	    xmlFree(self->percent);
	if (self->permille)
	    xmlFree(self->permille);
	if (self->zeroDigit)
	    xmlFree(self->zeroDigit);
	if (self->minusSign)
	    xmlFree(self->minusSign);
	if (self->infinity)
	    xmlFree(self->infinity);
	if (self->noNumber)
	    xmlFree(self->noNumber);
	if (self->name)
	    xmlFree(self->name);
	xmlFree(self);
    }
}