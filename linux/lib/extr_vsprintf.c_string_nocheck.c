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
 char* widen_string (char*,int,char*,struct printf_spec) ; 

__attribute__((used)) static char *string_nocheck(char *buf, char *end, const char *s,
			    struct printf_spec spec)
{
	int len = 0;
	int lim = spec.precision;

	while (lim--) {
		char c = *s++;
		if (!c)
			break;
		if (buf < end)
			*buf = c;
		++buf;
		++len;
	}
	return widen_string(buf, len, end, spec);
}