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
 char* escape_single_quotes_ascii (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 

__attribute__((used)) static char *
escape_quotes(const char *src)
{
	char	   *result = escape_single_quotes_ascii(src);

	if (!result)
	{
		pg_log_error("out of memory");
		exit(1);
	}
	return result;
}