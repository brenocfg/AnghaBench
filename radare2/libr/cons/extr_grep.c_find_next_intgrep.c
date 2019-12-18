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
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 scalar_t__ r_str_firstbut (char*,char,char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *find_next_intgrep(char *cmd, const char *quotes) {
	char *p;
	do {
		p = (char *)r_str_firstbut (cmd, '~', quotes);
		if (!p) {
			break;
		}
		if (p == cmd || *(p - 1) != '\\') {
			return (char*)p;
		}
		//twiddle unescape
		memmove (p - 1, p, strlen(p) + 1);
		cmd = p + 1;
	} while (*cmd);
	return NULL;
}