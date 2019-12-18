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
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 unsigned long long strtoll (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long long parse_number(const char *str)
{
	unsigned long long n;

	n = strtoll(str, NULL, 0);

	if (n == 0 && str[0] != '0')
		fatal("invalid name or number: %s\n", str);

	return n;
}