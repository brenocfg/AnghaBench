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
typedef  int /*<<< orphan*/  systick_dispatch_t ;

/* Variables and functions */
 int /*<<< orphan*/ * systick_dispatch_table ; 

__attribute__((used)) static inline void systick_enable_dispatch(size_t slot, systick_dispatch_t f) {
    systick_dispatch_table[slot] = f;
}