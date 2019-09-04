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

__attribute__((used)) static __inline void swap_bytes(ut8 *a, ut8 *b) {
	if (a != b) {
		ut8 temp = *a;
		*a = *b;
		*b = temp;
	}
}