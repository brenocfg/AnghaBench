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
struct pg_tm {int dummy; } ;
typedef  enum warn { ____Placeholder_warn } warn ;

/* Variables and functions */
 int IN_NONE ; 
 char* _fmt (char const*,struct pg_tm const*,char*,char*,int*) ; 

size_t
pg_strftime(char *s, size_t maxsize, const char *format, const struct pg_tm *t)
{
	char	   *p;
	enum warn	warn = IN_NONE;

	p = _fmt(format, t, s, s + maxsize, &warn);
	if (p == s + maxsize)
		return 0;
	*p = '\0';
	return p - s;
}