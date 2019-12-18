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
struct tm {int tm_year; int tm_mon; int tm_mday; } ;
typedef  scalar_t__ date ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDateTime (struct tm*) ; 
 scalar_t__ date2j (int,int,int) ; 
 scalar_t__ errno ; 

void
PGTYPESdate_today(date * d)
{
	struct tm	ts;

	GetCurrentDateTime(&ts);
	if (errno == 0)
		*d = date2j(ts.tm_year, ts.tm_mon, ts.tm_mday) - date2j(2000, 1, 1);
	return;
}