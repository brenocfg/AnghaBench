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
typedef  int /*<<< orphan*/  Numeric ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numeric_cmp ; 

__attribute__((used)) static int
compareNumeric(Numeric a, Numeric b)
{
	return DatumGetInt32(DirectFunctionCall2(numeric_cmp,
											 NumericGetDatum(a),
											 NumericGetDatum(b)));
}