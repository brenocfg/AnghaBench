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
typedef  double float8 ;
struct TYPE_4__ {double B; double A; double C; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_1__ LINE ;

/* Variables and functions */
 scalar_t__ FPeq (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPzero (double) ; 
 double float8_div (double,double) ; 
 double float8_mi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float8_mul (double,double) ; 
 double float8_pl (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  point_construct (int /*<<< orphan*/ *,double,double) ; 

__attribute__((used)) static bool
line_interpt_line(Point *result, LINE *l1, LINE *l2)
{
	float8		x,
				y;

	if (!FPzero(l1->B))
	{
		if (FPeq(l2->A, float8_mul(l1->A, float8_div(l2->B, l1->B))))
			return false;

		x = float8_div(float8_mi(float8_mul(l1->B, l2->C),
								 float8_mul(l2->B, l1->C)),
					   float8_mi(float8_mul(l1->A, l2->B),
								 float8_mul(l2->A, l1->B)));
		y = float8_div(-float8_pl(float8_mul(l1->A, x), l1->C), l1->B);
	}
	else if (!FPzero(l2->B))
	{
		if (FPeq(l1->A, float8_mul(l2->A, float8_div(l1->B, l2->B))))
			return false;

		x = float8_div(float8_mi(float8_mul(l2->B, l1->C),
								 float8_mul(l1->B, l2->C)),
					   float8_mi(float8_mul(l2->A, l1->B),
								 float8_mul(l1->A, l2->B)));
		y = float8_div(-float8_pl(float8_mul(l2->A, x), l2->C), l2->B);
	}
	else
		return false;

	/* On some platforms, the preceding expressions tend to produce -0. */
	if (x == 0.0)
		x = 0.0;
	if (y == 0.0)
		y = 0.0;

	if (result != NULL)
		point_construct(result, x, y);

	return true;
}