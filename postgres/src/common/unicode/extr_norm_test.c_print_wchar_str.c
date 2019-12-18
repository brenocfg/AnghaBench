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
typedef  int pg_wchar ;

/* Variables and functions */
 int BUF_DIGITS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 

__attribute__((used)) static char *
print_wchar_str(const pg_wchar *s)
{
#define BUF_DIGITS 50
	static char buf[BUF_DIGITS * 2 + 1];
	int			i;

	i = 0;
	while (*s && i < BUF_DIGITS)
	{
		snprintf(&buf[i * 2], 3, "%04X", *s);
		i++;
		s++;
	}
	buf[i * 2] = '\0';
	return buf;
}