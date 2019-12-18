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
struct pg_tm {int tm_mday; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustFractSeconds (double,struct pg_tm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECS_PER_DAY ; 

__attribute__((used)) static void
AdjustFractDays(double frac, struct pg_tm *tm, fsec_t *fsec, int scale)
{
	int			extra_days;

	if (frac == 0)
		return;
	frac *= scale;
	extra_days = (int) frac;
	tm->tm_mday += extra_days;
	frac -= extra_days;
	AdjustFractSeconds(frac, tm, fsec, SECS_PER_DAY);
}