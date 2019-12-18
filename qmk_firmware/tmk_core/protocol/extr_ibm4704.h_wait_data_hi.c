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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  data_in () ; 

__attribute__((used)) static inline uint16_t wait_data_hi(uint16_t us) {
    while (!data_in() && us) {
        asm("");
        _delay_us(1);
        us--;
    }
    return us;
}