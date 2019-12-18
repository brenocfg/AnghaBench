#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ timestamp ;
struct TYPE_3__ {scalar_t__ month; scalar_t__ time; } ;
typedef  TYPE_1__ interval ;

/* Variables and functions */
 int PGTYPES_TS_ERR_EINFTIME ; 
 scalar_t__ TIMESTAMP_NOT_FINITE (scalar_t__) ; 

int
PGTYPEStimestamp_sub(timestamp * ts1, timestamp * ts2, interval * iv)
{
	if (TIMESTAMP_NOT_FINITE(*ts1) || TIMESTAMP_NOT_FINITE(*ts2))
		return PGTYPES_TS_ERR_EINFTIME;
	else
		iv->time = (*ts1 - *ts2);

	iv->month = 0;

	return 0;
}