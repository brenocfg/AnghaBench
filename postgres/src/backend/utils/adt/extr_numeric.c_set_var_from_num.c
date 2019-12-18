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
struct TYPE_4__ {int /*<<< orphan*/  digits; int /*<<< orphan*/  dscale; int /*<<< orphan*/  sign; int /*<<< orphan*/  weight; } ;
typedef  TYPE_1__ NumericVar ;
typedef  int /*<<< orphan*/  NumericDigit ;
typedef  int /*<<< orphan*/  Numeric ;

/* Variables and functions */
 int /*<<< orphan*/  NUMERIC_DIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_DSCALE (int /*<<< orphan*/ ) ; 
 int NUMERIC_NDIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_SIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_WEIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_var_from_num(Numeric num, NumericVar *dest)
{
	int			ndigits;

	ndigits = NUMERIC_NDIGITS(num);

	alloc_var(dest, ndigits);

	dest->weight = NUMERIC_WEIGHT(num);
	dest->sign = NUMERIC_SIGN(num);
	dest->dscale = NUMERIC_DSCALE(num);

	memcpy(dest->digits, NUMERIC_DIGITS(num), ndigits * sizeof(NumericDigit));
}