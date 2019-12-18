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

/* Variables and functions */
 int /*<<< orphan*/  isoweek2j (int,int) ; 
 int /*<<< orphan*/  j2date (int /*<<< orphan*/ ,int*,int*,int*) ; 

void
isoweek2date(int woy, int *year, int *mon, int *mday)
{
	j2date(isoweek2j(*year, woy), year, mon, mday);
}