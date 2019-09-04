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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  dt ;

/* Variables and functions */
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

int fetch_current_timestamp(char *buf, size_t sz)
{
	struct timeval tv;
	struct tm tm;
	char dt[32];

	if (gettimeofday(&tv, NULL) || !localtime_r(&tv.tv_sec, &tm))
		return -1;

	if (!strftime(dt, sizeof(dt), "%Y%m%d%H%M%S", &tm))
		return -1;

	scnprintf(buf, sz, "%s%02u", dt, (unsigned)tv.tv_usec / 10000);

	return 0;
}