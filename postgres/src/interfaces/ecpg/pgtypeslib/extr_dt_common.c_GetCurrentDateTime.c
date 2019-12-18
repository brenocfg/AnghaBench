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
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abstime2tm (int /*<<< orphan*/ ,int*,struct tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
GetCurrentDateTime(struct tm *tm)
{
	int			tz;

	abstime2tm(time(NULL), &tz, tm, NULL);
}