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
 int /*<<< orphan*/  PG_UTF8 ; 
 char* pg_server_to_any (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline char *
utf_e2u(const char *str)
{
	char	   *ret;

	ret = pg_server_to_any(str, strlen(str), PG_UTF8);

	/* ensure we have a copy even if no conversion happened */
	if (ret == str)
		ret = pstrdup(ret);

	return ret;
}