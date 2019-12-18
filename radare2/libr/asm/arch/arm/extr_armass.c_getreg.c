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
 int /*<<< orphan*/  strcmpnull (char const*,char const*) ; 
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static int getreg(const char *str) {
	int i;
	char *ep;
	const char *aliases[] = { "sl", "fp", "ip", "sp", "lr", "pc", NULL };
	if (!str || !*str) {
		return -1;
	}
	if (*str == 'r') {
		int reg = strtol (str + 1, &ep, 10);
		if ((ep[0] != '\0') || (str[1] == '\0')) {
			return -1;
		}
		if (reg < 16 && reg >= 0) {
			return reg;
		}
	}
	for (i=0; aliases[i]; i++) {
		if (!strcmpnull (str, aliases[i])) {
			return 10 + i;
		}
	}
	return -1;
}