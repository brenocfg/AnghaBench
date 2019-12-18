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

__attribute__((used)) static bool get_arg(char const*multi, int n, char * dest)
{
	char* lastnonws = dest;
	bool anynonws = false;
	bool in_string = false;
	n -= 1;
	if (!multi) return false;
	while (n && *multi && *multi != '\n' && *multi != '\r') {
		if (*multi == '\'') in_string = !in_string;
		if (!in_string) {
			if (*multi == ';') {
				return false;
			}
			if (*multi == ',') {
				multi += 1;
				n -= 1;
				continue;
			}
		}
		multi += 1;
	}
	if (!*multi || *multi == '\n' || *multi == '\r' || in_string) {
		return false;
	}

	while (*multi && (*multi == ' ' || *multi == '\t')) {
		multi += 1;
	}

	while (*multi && *multi != '\n' && *multi != '\r') {
		if (*multi == '\'') in_string = !in_string;
		if (!in_string) {
			if (*multi == ';' ||  *multi == ',') {
				break;
			}
			if (*multi != ' ' && *multi != '\t') {
				lastnonws = dest;
				anynonws = true;
			}
			*dest = *multi;
			dest += 1;
			multi += 1;
		}
	}

	if (in_string) return false;

	if (!anynonws) {
		*dest = '\0';
		return false;
	}
	*(lastnonws + 1) = '\0';
	return true;
}