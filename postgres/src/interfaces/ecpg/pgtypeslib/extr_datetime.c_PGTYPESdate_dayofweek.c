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

int
PGTYPESdate_dayofweek(date dDate)
{
	/*
	 * Sunday:	0 Monday:	   1 Tuesday:	  2 Wednesday:	 3 Thursday: 4
	 * Friday:		5 Saturday:    6
	 */
	return (int) (dDate + date2j(2000, 1, 1) + 1) % 7;
}