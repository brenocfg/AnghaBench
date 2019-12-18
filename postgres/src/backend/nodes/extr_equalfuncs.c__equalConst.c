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
struct TYPE_4__ {int /*<<< orphan*/  constlen; int /*<<< orphan*/  constbyval; int /*<<< orphan*/  constvalue; scalar_t__ constisnull; } ;
typedef  TYPE_1__ Const ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constbyval ; 
 int /*<<< orphan*/  constcollid ; 
 int /*<<< orphan*/  constisnull ; 
 int /*<<< orphan*/  constlen ; 
 int /*<<< orphan*/  consttype ; 
 int /*<<< orphan*/  consttypmod ; 
 int datumIsEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location ; 

__attribute__((used)) static bool
_equalConst(const Const *a, const Const *b)
{
	COMPARE_SCALAR_FIELD(consttype);
	COMPARE_SCALAR_FIELD(consttypmod);
	COMPARE_SCALAR_FIELD(constcollid);
	COMPARE_SCALAR_FIELD(constlen);
	COMPARE_SCALAR_FIELD(constisnull);
	COMPARE_SCALAR_FIELD(constbyval);
	COMPARE_LOCATION_FIELD(location);

	/*
	 * We treat all NULL constants of the same type as equal. Someday this
	 * might need to change?  But datumIsEqual doesn't work on nulls, so...
	 */
	if (a->constisnull)
		return true;
	return datumIsEqual(a->constvalue, b->constvalue,
						a->constbyval, a->constlen);
}