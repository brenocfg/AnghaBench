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
typedef  int /*<<< orphan*/  int64 ;

/* Variables and functions */
 scalar_t__ GetEpochTime (struct tm*) ; 
 int /*<<< orphan*/  tm2timestamp (struct tm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static timestamp
SetEpochTimestamp(void)
{
	int64		noresult = 0;
	timestamp	dt;
	struct tm	tt,
			   *tm = &tt;

	if (GetEpochTime(tm) < 0)
		return noresult;

	tm2timestamp(tm, 0, NULL, &dt);
	return dt;
}