#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  double float8 ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {TYPE_2__ low; TYPE_1__ high; } ;
typedef  TYPE_3__ BOX ;

/* Variables and functions */
 scalar_t__ float8_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float8_mi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double float8_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double get_float8_infinity () ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static float8
size_box(const BOX *box)
{
	/*
	 * Check for zero-width cases.  Note that we define the size of a zero-
	 * by-infinity box as zero.  It's important to special-case this somehow,
	 * as naively multiplying infinity by zero will produce NaN.
	 *
	 * The less-than cases should not happen, but if they do, say "zero".
	 */
	if (float8_le(box->high.x, box->low.x) ||
		float8_le(box->high.y, box->low.y))
		return 0.0;

	/*
	 * We treat NaN as larger than +Infinity, so any distance involving a NaN
	 * and a non-NaN is infinite.  Note the previous check eliminated the
	 * possibility that the low fields are NaNs.
	 */
	if (isnan(box->high.x) || isnan(box->high.y))
		return get_float8_infinity();
	return float8_mul(float8_mi(box->high.x, box->low.x),
					  float8_mi(box->high.y, box->low.y));
}