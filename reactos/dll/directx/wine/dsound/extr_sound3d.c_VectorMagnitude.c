#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ D3DVECTOR ;
typedef  int /*<<< orphan*/  D3DVALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ScalarProduct (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline D3DVALUE VectorMagnitude (const D3DVECTOR *a)
{
	D3DVALUE l;
	l = sqrt (ScalarProduct (a, a));
	TRACE("|(%f,%f,%f)| = %f\n", a->x, a->y, a->z, l);
	return l;
}