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
 scalar_t__ is_space (int) ; 

__attribute__((used)) static inline int check_space(int t, int *spc)
{
	if (is_space (t)) {
		if (*spc) {
			return 1;
		}
		*spc = 1;
	} else {
		*spc = 0;
	}
	return 0;
}