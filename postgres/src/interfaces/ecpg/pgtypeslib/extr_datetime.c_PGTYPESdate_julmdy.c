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
typedef  scalar_t__ date ;

/* Variables and functions */
 scalar_t__ date2j (int,int,int) ; 
 int /*<<< orphan*/  j2date (int,int*,int*,int*) ; 

void
PGTYPESdate_julmdy(date jd, int *mdy)
{
	int			y,
				m,
				d;

	j2date((int) (jd + date2j(2000, 1, 1)), &y, &m, &d);
	mdy[0] = m;
	mdy[1] = d;
	mdy[2] = y;
}