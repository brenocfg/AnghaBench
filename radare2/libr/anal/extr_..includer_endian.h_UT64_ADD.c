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
typedef  scalar_t__ ut64 ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 

__attribute__((used)) static inline int UT64_ADD(ut64 *r, ut64 a, ut64 b) {
	if (UT64_MAX - a < b) {
		return 0;
	}
	if (r) {
		*r = a + b;
	}
	return 1;
}