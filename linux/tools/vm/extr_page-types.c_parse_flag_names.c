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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  parse_flag_name (char const*,int) ; 

__attribute__((used)) static uint64_t parse_flag_names(const char *str, int all)
{
	const char *p    = str;
	uint64_t   flags = 0;

	while (1) {
		if (*p == ',' || *p == '=' || *p == '\0') {
			if ((*str != '~') || (*str == '~' && all && *++str))
				flags |= parse_flag_name(str, p - str);
			if (*p != ',')
				break;
			str = p + 1;
		}
		p++;
	}

	return flags;
}