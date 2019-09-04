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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 scalar_t__ ZLOG_DEBUG ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/  const*,struct tm*) ; 
 scalar_t__ snprintf (char*,size_t,char*,...) ; 
 size_t strftime (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zlog_level ; 

size_t zlog_print_time(struct timeval *tv, char *timebuf, size_t timebuf_len) /* {{{ */
{
	struct tm t;
	size_t len;

	len = strftime(timebuf, timebuf_len, "[%d-%b-%Y %H:%M:%S",
			localtime_r((const time_t *) &tv->tv_sec, &t));
	if (zlog_level == ZLOG_DEBUG) {
		len += snprintf(timebuf + len, timebuf_len - len, ".%06d", (int) tv->tv_usec);
	}
	len += snprintf(timebuf + len, timebuf_len - len, "] ");
	return len;
}