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
struct pg_tm {int tm_sec; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 scalar_t__ rint (double) ; 

__attribute__((used)) static void
AdjustFractSeconds(double frac, struct pg_tm *tm, fsec_t *fsec, int scale)
{
	int			sec;

	if (frac == 0)
		return;
	frac *= scale;
	sec = (int) frac;
	tm->tm_sec += sec;
	frac -= sec;
	*fsec += rint(frac * 1000000);
}