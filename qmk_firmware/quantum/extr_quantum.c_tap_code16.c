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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAP_CODE_DELAY ; 
 int /*<<< orphan*/  register_code16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ms (int /*<<< orphan*/ ) ; 

void tap_code16(uint16_t code) {
    register_code16(code);
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    unregister_code16(code);
}