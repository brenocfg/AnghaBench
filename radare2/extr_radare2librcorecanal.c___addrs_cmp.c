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
 scalar_t__ r_num_get (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int __addrs_cmp(void *_a, void *_b) {
	ut64 a = r_num_get (NULL, _a);
	ut64 b = r_num_get (NULL, _b);
	if (a > b) {
		return 1;
	}
	if (a < b) {
		return -1;
	}
        return 0;
}