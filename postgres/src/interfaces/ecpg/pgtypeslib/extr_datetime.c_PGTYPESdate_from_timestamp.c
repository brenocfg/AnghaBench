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
typedef  int timestamp ;
typedef  int date ;

/* Variables and functions */
 int /*<<< orphan*/  TIMESTAMP_NOT_FINITE (int) ; 
 int USECS_PER_DAY ; 

date
PGTYPESdate_from_timestamp(timestamp dt)
{
	date		dDate;

	dDate = 0;					/* suppress compiler warning */

	if (!TIMESTAMP_NOT_FINITE(dt))
	{
		/* Microseconds to days */
		dDate = (dt / USECS_PER_DAY);
	}

	return dDate;
}