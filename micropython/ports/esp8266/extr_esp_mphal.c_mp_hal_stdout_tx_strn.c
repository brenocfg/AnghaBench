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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_uos_dupterm_tx_strn (char const*,int /*<<< orphan*/ ) ; 

void mp_hal_stdout_tx_strn(const char *str, uint32_t len) {
    mp_uos_dupterm_tx_strn(str, len);
}