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
typedef  int /*<<< orphan*/  ut64 ;

/* Variables and functions */
 int err ; 
 int /*<<< orphan*/  strtoll (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut64 getnum(const char *str) {
	char *endptr;
	err = false;
	ut64 val;

	if (!str) {
		err = true;
		return 0;
	}
	while (*str == '$' || *str == '#') {
		str++;
	}
	val = strtoll (str, &endptr, 0);
	if (str != endptr && *endptr == '\0') {
		return val;
	}
	err = true;
	return 0;
}