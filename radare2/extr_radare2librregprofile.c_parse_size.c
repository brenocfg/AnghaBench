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
typedef  int ut64 ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 int strtoul (char*,char**,int) ; 

__attribute__((used)) static ut64 parse_size(char *s, char **end) {
	if (*s == '.') {
		return strtoul (s + 1, end, 10);
	}
	char *has_dot = strchr (s, '.');
	if (has_dot) {
		*has_dot++ = 0;
		ut64 a = strtoul (s, end, 0) << 3;
		ut64 b = strtoul (has_dot, end, 0);
		return a + b;
	}
	return strtoul (s, end, 0) << 3;
}