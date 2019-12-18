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
typedef  scalar_t__ ut16 ;

/* Variables and functions */
 scalar_t__ UT16_MAX ; 

__attribute__((used)) static inline int UT16_ADD(ut16 *r, ut16 a, ut16 b) {
	if (UT16_MAX - a < b) {
		return 0;
	}
	if (r) {
		*r = a + b;
	}
	return 1;
}