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
struct timeval {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_asctime_r (struct tm*,char*) ; 
 int /*<<< orphan*/  php_localtime_r (int /*<<< orphan*/ *,struct tm*) ; 

int php_cli_server_get_system_time(char *buf) {
	struct timeval tv;
	struct tm tm;

	gettimeofday(&tv, NULL);

	/* TODO: should be checked for NULL tm/return vaue */
	php_localtime_r(&tv.tv_sec, &tm);
	php_asctime_r(&tm, buf);
	return 0;
}