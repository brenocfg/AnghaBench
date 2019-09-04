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

/* Variables and functions */
 struct tm* php_gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static int date_to_ISO8601 (time_t value, char *buf, int length) {
   struct tm *tm, tmbuf;
   tm = php_gmtime_r(&value, &tmbuf);
   if (!tm) {
	   return 0;
   }
#if 0  /* TODO: soap seems to favor this method. xmlrpc the latter. */
	return strftime (buf, length, "%Y-%m-%dT%H:%M:%SZ", tm);
#else
   return strftime(buf, length, "%Y%m%dT%H:%M:%SZ", tm);
#endif
}