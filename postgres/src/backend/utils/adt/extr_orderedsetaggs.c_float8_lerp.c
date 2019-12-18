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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 double DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Float8GetDatum (double) ; 

__attribute__((used)) static Datum
float8_lerp(Datum lo, Datum hi, double pct)
{
	double		loval = DatumGetFloat8(lo);
	double		hival = DatumGetFloat8(hi);

	return Float8GetDatum(loval + (pct * (hival - loval)));
}