#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SortSupport ;
typedef  scalar_t__ Pointer ;
typedef  scalar_t__ Numeric ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetNumeric (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int cmp_numerics (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

__attribute__((used)) static int
numeric_fast_cmp(Datum x, Datum y, SortSupport ssup)
{
	Numeric		nx = DatumGetNumeric(x);
	Numeric		ny = DatumGetNumeric(y);
	int			result;

	result = cmp_numerics(nx, ny);

	if ((Pointer) nx != DatumGetPointer(x))
		pfree(nx);
	if ((Pointer) ny != DatumGetPointer(y))
		pfree(ny);

	return result;
}