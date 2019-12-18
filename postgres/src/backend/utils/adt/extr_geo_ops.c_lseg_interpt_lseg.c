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
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_1__ LSEG ;
typedef  int /*<<< orphan*/  LINE ;

/* Variables and functions */
 int /*<<< orphan*/  line_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseg_contain_point (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseg_interpt_line (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lseg_sl (TYPE_1__*) ; 

__attribute__((used)) static bool
lseg_interpt_lseg(Point *result, LSEG *l1, LSEG *l2)
{
	Point		interpt;
	LINE		tmp;

	line_construct(&tmp, &l2->p[0], lseg_sl(l2));
	if (!lseg_interpt_line(&interpt, l1, &tmp))
		return false;

	/*
	 * If the line intersection point isn't within l2, there is no valid
	 * segment intersection point at all.
	 */
	if (!lseg_contain_point(l2, &interpt))
		return false;

	if (result != NULL)
		*result = interpt;

	return true;
}