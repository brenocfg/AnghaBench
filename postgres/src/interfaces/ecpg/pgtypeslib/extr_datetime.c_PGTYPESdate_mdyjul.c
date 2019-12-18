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

void
PGTYPESdate_mdyjul(int *mdy, date * jdate)
{
	/* month is mdy[0] */
	/* day	 is mdy[1] */
	/* year  is mdy[2] */

	*jdate = (date) (date2j(mdy[2], mdy[0], mdy[1]) - date2j(2000, 1, 1));
}