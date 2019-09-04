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
typedef  scalar_t__ ut32 ;

/* Variables and functions */

__attribute__((used)) static inline int UT32_SUB(ut32 *r, ut32 a, ut32 b) {
	if (b > a) {
		return 0;
	}
	if (r) {
		*r = a - b;
	}
	return 1;
}