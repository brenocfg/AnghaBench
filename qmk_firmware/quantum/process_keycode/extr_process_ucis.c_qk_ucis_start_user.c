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
 int /*<<< orphan*/  register_hex (int) ; 
 int /*<<< orphan*/  unicode_input_finish () ; 
 int /*<<< orphan*/  unicode_input_start () ; 

__attribute__((weak)) void qk_ucis_start_user(void) {
    unicode_input_start();
    register_hex(0x2328);
    unicode_input_finish();
}