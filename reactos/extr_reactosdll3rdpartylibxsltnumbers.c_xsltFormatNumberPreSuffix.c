#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltFormatNumberInfoPtr ;
typedef  TYPE_2__* xsltDecimalFormatPtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_7__ {int /*<<< orphan*/  permille; int /*<<< orphan*/  percent; } ;
struct TYPE_6__ {int multiplier; void* is_multiplier_set; } ;

/* Variables and functions */
 scalar_t__ IS_SPECIAL (TYPE_2__*,scalar_t__*) ; 
 scalar_t__ SYMBOL_QUOTE ; 
 void* TRUE ; 
 int xmlUTF8Strsize (scalar_t__*,int) ; 
 scalar_t__ xsltUTF8Charcmp (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xsltFormatNumberPreSuffix(xsltDecimalFormatPtr self, xmlChar **format, xsltFormatNumberInfoPtr info)
{
    int	count=0;	/* will hold total length of prefix/suffix */
    int len;

    while (1) {
	/*
	 * prefix / suffix ends at end of string or at
	 * first 'special' character
	 */
	if (**format == 0)
	    return count;
	/* if next character 'escaped' just count it */
	if (**format == SYMBOL_QUOTE) {
	    if (*++(*format) == 0)
		return -1;
	}
	else if (IS_SPECIAL(self, *format))
	    return count;
	/*
	 * else treat percent/per-mille as special cases,
	 * depending on whether +ve or -ve
	 */
	else {
	    /*
	     * for +ve prefix/suffix, allow only a
	     * single occurence of either
	     */
	    if (xsltUTF8Charcmp(*format, self->percent) == 0) {
		if (info->is_multiplier_set)
		    return -1;
		info->multiplier = 100;
		info->is_multiplier_set = TRUE;
	    } else if (xsltUTF8Charcmp(*format, self->permille) == 0) {
		if (info->is_multiplier_set)
		    return -1;
		info->multiplier = 1000;
		info->is_multiplier_set = TRUE;
	    }
	}

	if ((len=xmlUTF8Strsize(*format, 1)) < 1)
	    return -1;
	count += len;
	*format += len;
    }
}