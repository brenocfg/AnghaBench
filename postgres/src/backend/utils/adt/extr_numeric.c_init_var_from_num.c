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
struct TYPE_3__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/  digits; int /*<<< orphan*/  dscale; int /*<<< orphan*/  sign; int /*<<< orphan*/  weight; int /*<<< orphan*/  ndigits; } ;
typedef  TYPE_1__ NumericVar ;
typedef  int /*<<< orphan*/  Numeric ;

/* Variables and functions */
 int /*<<< orphan*/  NUMERIC_DIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_DSCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_NDIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_SIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_WEIGHT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_var_from_num(Numeric num, NumericVar *dest)
{
	dest->ndigits = NUMERIC_NDIGITS(num);
	dest->weight = NUMERIC_WEIGHT(num);
	dest->sign = NUMERIC_SIGN(num);
	dest->dscale = NUMERIC_DSCALE(num);
	dest->digits = NUMERIC_DIGITS(num);
	dest->buf = NULL;			/* digits array is not palloc'd */
}