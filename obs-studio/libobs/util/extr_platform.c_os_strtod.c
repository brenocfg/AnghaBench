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

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 double strtod (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_locale (char*) ; 

double os_strtod(const char *str)
{
	char buf[64];
	snprintf(buf, 64, "%s", str);
	to_locale(buf);
	return strtod(buf, NULL);
}