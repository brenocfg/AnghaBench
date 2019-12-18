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

__attribute__((used)) static size_t countMatching (const char *a, const char *b) {
	size_t matches = 0;
	for (; *a && *b; a++, b++) {
		if (*a != *b) {
			break;
		}
		matches++;
	}
	return matches;
}