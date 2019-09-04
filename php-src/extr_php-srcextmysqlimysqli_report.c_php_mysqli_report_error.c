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
 int /*<<< orphan*/  php_mysqli_throw_sql_exception (char*,int,char*,char const*) ; 

void php_mysqli_report_error(const char *sqlstate, int errorno, const char *error)
{
	php_mysqli_throw_sql_exception((char *)sqlstate, errorno, "%s", error);
}