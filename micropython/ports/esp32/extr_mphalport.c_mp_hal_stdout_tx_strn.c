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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_THREAD_GIL_ENTER () ; 
 int /*<<< orphan*/  MP_THREAD_GIL_EXIT () ; 
 int /*<<< orphan*/  mp_uos_dupterm_tx_strn (char const*,int) ; 
 int /*<<< orphan*/  uart_tx_one_char (char const) ; 

void mp_hal_stdout_tx_strn(const char *str, uint32_t len) {
    // Only release the GIL if many characters are being sent
    bool release_gil = len > 20;
    if (release_gil) {
        MP_THREAD_GIL_EXIT();
    }
    for (uint32_t i = 0; i < len; ++i) {
        uart_tx_one_char(str[i]);
    }
    if (release_gil) {
        MP_THREAD_GIL_ENTER();
    }
    mp_uos_dupterm_tx_strn(str, len);
}