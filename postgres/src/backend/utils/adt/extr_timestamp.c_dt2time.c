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
typedef  int fsec_t ;
typedef  int Timestamp ;
typedef  int TimeOffset ;

/* Variables and functions */
 int USECS_PER_HOUR ; 
 int USECS_PER_MINUTE ; 
 int USECS_PER_SEC ; 

void
dt2time(Timestamp jd, int *hour, int *min, int *sec, fsec_t *fsec)
{
	TimeOffset	time;

	time = jd;

	*hour = time / USECS_PER_HOUR;
	time -= (*hour) * USECS_PER_HOUR;
	*min = time / USECS_PER_MINUTE;
	time -= (*min) * USECS_PER_MINUTE;
	*sec = time / USECS_PER_SEC;
	*fsec = time - (*sec * USECS_PER_SEC);
}