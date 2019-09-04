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

__attribute__((used)) static inline int strstr2(const char *a, const char *b, int n) {
	int i, j;
	for (i = j = 0; a[i] && b[j] && j < n; i++) {
		if (a[i] == b[j]) {
			j++;
		} else {
			j = 0;
		}
	}
	return j == n;
}