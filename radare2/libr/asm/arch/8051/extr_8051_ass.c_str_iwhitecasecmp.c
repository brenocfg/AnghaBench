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
 scalar_t__ isspace (char const) ; 
 scalar_t__ tolower (char const) ; 

__attribute__((used)) static int str_iwhitecasecmp(char const*a, char const*b) {
	if (!a && !b) {
		return *a - *b;
	}
	while (a && b) {
		if (!*a && !*b) {
			break;
		}
		if (!*a || !*b) {
			break;
		}
		if (isspace (*a)) {
			a += 1;
			continue;
		}
		if (isspace (*b)) {
			b += 1;
			continue;
		}
		if (tolower (*a) == tolower (*b)) {
			a += 1;
			b += 1;
			continue;
		}
		break;
	}
	return *a - *b;
}