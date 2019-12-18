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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 scalar_t__ tolower (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline int mycmp(const char *a, const char *b, int n, int any) {
	int i, j;
	for (i = j = 0; a[i] && b[j] && j < n; i++) {
		if (tolower ((const ut8)a[i]) == tolower ((const ut8)b[j])) {
			j++;
		} else {
			if (!any) {
				return 0;
			}
			j = 0;
		}
	}
	return any? j != n: 1;
}