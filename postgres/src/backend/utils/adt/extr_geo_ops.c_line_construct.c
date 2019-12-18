#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  double float8 ;
struct TYPE_6__ {double A; double B; double C; } ;
struct TYPE_5__ {double x; int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ Point ;
typedef  TYPE_2__ LINE ;

/* Variables and functions */
 double DBL_MAX ; 
 double float8_mi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float8_mul (double,double) ; 

__attribute__((used)) static inline void
line_construct(LINE *result, Point *pt, float8 m)
{
	if (m == DBL_MAX)
	{
		/* vertical - use "x = C" */
		result->A = -1.0;
		result->B = 0.0;
		result->C = pt->x;
	}
	else
	{
		/* use "mx - y + yinter = 0" */
		result->A = m;
		result->B = -1.0;
		result->C = float8_mi(pt->y, float8_mul(m, pt->x));
		/* on some platforms, the preceding expression tends to produce -0 */
		if (result->C == 0.0)
			result->C = 0.0;
	}
}