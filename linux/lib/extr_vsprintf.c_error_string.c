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
struct printf_spec {int precision; } ;

/* Variables and functions */
 char* string_nocheck (char*,char*,char const*,struct printf_spec) ; 

__attribute__((used)) static char *error_string(char *buf, char *end, const char *s,
			  struct printf_spec spec)
{
	/*
	 * Hard limit to avoid a completely insane messages. It actually
	 * works pretty well because most error messages are in
	 * the many pointer format modifiers.
	 */
	if (spec.precision == -1)
		spec.precision = 2 * sizeof(void *);

	return string_nocheck(buf, end, s, spec);
}