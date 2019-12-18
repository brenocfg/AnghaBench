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
 scalar_t__ r_str_startswith (char const*,char*) ; 
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static int getcoprocreg(const char *str) {
	char *ep;
	
	if (!str || !*str) {
		return -1;
	}
	if (r_str_startswith (str, "c")) {
		int reg = strtol (str + 1, &ep, 10);
		if ((ep[0] != '\0') || (str[1] == '\0')) {
			return -1;
		}
		if (reg < 16 && reg >= 0) {
			return reg;
		}
	}
	return -1;
}