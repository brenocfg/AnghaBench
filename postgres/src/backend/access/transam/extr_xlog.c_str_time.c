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
typedef  int /*<<< orphan*/  pg_time_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  log_timezone ; 
 int /*<<< orphan*/  pg_localtime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strftime (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
str_time(pg_time_t tnow)
{
	static char buf[128];

	pg_strftime(buf, sizeof(buf),
				"%Y-%m-%d %H:%M:%S %Z",
				pg_localtime(&tnow, log_timezone));

	return buf;
}