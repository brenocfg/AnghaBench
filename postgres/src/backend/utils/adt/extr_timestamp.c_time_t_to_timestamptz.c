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
typedef  scalar_t__ pg_time_t ;
typedef  scalar_t__ TimestampTz ;

/* Variables and functions */
 int POSTGRES_EPOCH_JDATE ; 
 int SECS_PER_DAY ; 
 int UNIX_EPOCH_JDATE ; 
 scalar_t__ USECS_PER_SEC ; 

TimestampTz
time_t_to_timestamptz(pg_time_t tm)
{
	TimestampTz result;

	result = (TimestampTz) tm -
		((POSTGRES_EPOCH_JDATE - UNIX_EPOCH_JDATE) * SECS_PER_DAY);
	result *= USECS_PER_SEC;

	return result;
}