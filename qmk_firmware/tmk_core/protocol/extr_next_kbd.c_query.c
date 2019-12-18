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
 int /*<<< orphan*/  out_hi () ; 
 int /*<<< orphan*/  out_hi_delay (int) ; 
 int /*<<< orphan*/  out_lo_delay (int) ; 

__attribute__((used)) static inline void query(void) {
    out_lo_delay(5);
    out_hi_delay(1);
    out_lo_delay(3);
    out_hi();
}