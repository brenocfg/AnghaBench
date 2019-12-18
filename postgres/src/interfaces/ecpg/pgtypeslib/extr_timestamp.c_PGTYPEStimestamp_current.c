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
typedef  int /*<<< orphan*/  timestamp ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDateTime (struct tm*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  tm2timestamp (struct tm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
PGTYPEStimestamp_current(timestamp * ts)
{
	struct tm	tm;

	GetCurrentDateTime(&tm);
	if (errno == 0)
		tm2timestamp(&tm, 0, NULL, ts);
	return;
}