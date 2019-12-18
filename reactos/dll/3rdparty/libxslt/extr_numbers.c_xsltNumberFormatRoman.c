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
typedef  TYPE_1__* xsltNumberDataPtr ;
typedef  int /*<<< orphan*/  xmlBufferPtr ;
struct TYPE_3__ {int /*<<< orphan*/  groupingCharacterLen; int /*<<< orphan*/  groupingCharacter; int /*<<< orphan*/  digitsPerGroup; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlBufferCCat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltNumberFormatDecimal (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xsltNumberFormatRoman(xsltNumberDataPtr data,
		      xmlBufferPtr buffer,
		      double number,
		      int is_upper)
{
    /*
     * See discussion in xsltNumberFormatAlpha. Also use a reasonable upper
     * bound to avoid denial of service.
     */
    if (number < 1.0 || number > 5000.0) {
        xsltNumberFormatDecimal(buffer, number, '0', 1,
                                data->digitsPerGroup,
                                data->groupingCharacter,
                                data->groupingCharacterLen);
        return;
    }

    /*
     * Based on an example by Jim Walsh
     */
    while (number >= 1000.0) {
	xmlBufferCCat(buffer, (is_upper) ? "M" : "m");
	number -= 1000.0;
    }
    if (number >= 900.0) {
	xmlBufferCCat(buffer, (is_upper) ? "CM" : "cm");
	number -= 900.0;
    }
    while (number >= 500.0) {
	xmlBufferCCat(buffer, (is_upper) ? "D" : "d");
	number -= 500.0;
    }
    if (number >= 400.0) {
	xmlBufferCCat(buffer, (is_upper) ? "CD" : "cd");
	number -= 400.0;
    }
    while (number >= 100.0) {
	xmlBufferCCat(buffer, (is_upper) ? "C" : "c");
	number -= 100.0;
    }
    if (number >= 90.0) {
	xmlBufferCCat(buffer, (is_upper) ? "XC" : "xc");
	number -= 90.0;
    }
    while (number >= 50.0) {
	xmlBufferCCat(buffer, (is_upper) ? "L" : "l");
	number -= 50.0;
    }
    if (number >= 40.0) {
	xmlBufferCCat(buffer, (is_upper) ? "XL" : "xl");
	number -= 40.0;
    }
    while (number >= 10.0) {
	xmlBufferCCat(buffer, (is_upper) ? "X" : "x");
	number -= 10.0;
    }
    if (number >= 9.0) {
	xmlBufferCCat(buffer, (is_upper) ? "IX" : "ix");
	number -= 9.0;
    }
    while (number >= 5.0) {
	xmlBufferCCat(buffer, (is_upper) ? "V" : "v");
	number -= 5.0;
    }
    if (number >= 4.0) {
	xmlBufferCCat(buffer, (is_upper) ? "IV" : "iv");
	number -= 4.0;
    }
    while (number >= 1.0) {
	xmlBufferCCat(buffer, (is_upper) ? "I" : "i");
	number--;
    }
}