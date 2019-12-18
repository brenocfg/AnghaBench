#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ D3DVECTOR ;
typedef  int D3DVALUE ;

/* Variables and functions */
 int /*<<< orphan*/  RadToDeg (int) ; 
 int ScalarProduct (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int VectorMagnitude (TYPE_1__ const*) ; 
 int acos (int) ; 

__attribute__((used)) static inline D3DVALUE AngleBetweenVectorsRad (const D3DVECTOR *a, const D3DVECTOR *b)
{
	D3DVALUE la, lb, product, angle, cos;
	/* definition of scalar product: a*b = |a|*|b|*cos... therefore: */
	product = ScalarProduct (a,b);
	la = VectorMagnitude (a);
	lb = VectorMagnitude (b);
	if (!la || !lb)
		return 0;

	cos = product/(la*lb);
	angle = acos(cos);
	TRACE("angle between (%f,%f,%f) and (%f,%f,%f) = %f radians (%f degrees)\n",  a->x, a->y, a->z, b->x,
	      b->y, b->z, angle, RadToDeg(angle));
	return angle;	
}