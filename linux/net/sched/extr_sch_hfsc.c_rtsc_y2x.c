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
typedef  scalar_t__ u64 ;
struct runtime_sc {scalar_t__ y; scalar_t__ x; scalar_t__ dy; scalar_t__ dx; int /*<<< orphan*/  ism2; int /*<<< orphan*/  ism1; } ;

/* Variables and functions */
 scalar_t__ seg_y2x (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64
rtsc_y2x(struct runtime_sc *rtsc, u64 y)
{
	u64 x;

	if (y < rtsc->y)
		x = rtsc->x;
	else if (y <= rtsc->y + rtsc->dy) {
		/* x belongs to the 1st segment */
		if (rtsc->dy == 0)
			x = rtsc->x + rtsc->dx;
		else
			x = rtsc->x + seg_y2x(y - rtsc->y, rtsc->ism1);
	} else {
		/* x belongs to the 2nd segment */
		x = rtsc->x + rtsc->dx
		    + seg_y2x(y - rtsc->y - rtsc->dy, rtsc->ism2);
	}
	return x;
}