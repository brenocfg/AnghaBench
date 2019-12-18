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
struct trace_print_flags {unsigned long mask; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_flag_spec ; 
 int /*<<< orphan*/  default_str_spec ; 
 char* number (char*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 char* string (char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
char *format_flags(char *buf, char *end, unsigned long flags,
					const struct trace_print_flags *names)
{
	unsigned long mask;

	for ( ; flags && names->name; names++) {
		mask = names->mask;
		if ((flags & mask) != mask)
			continue;

		buf = string(buf, end, names->name, default_str_spec);

		flags &= ~mask;
		if (flags) {
			if (buf < end)
				*buf = '|';
			buf++;
		}
	}

	if (flags)
		buf = number(buf, end, flags, default_flag_spec);

	return buf;
}