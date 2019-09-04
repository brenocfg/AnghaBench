#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_4__ {scalar_t__ buf; } ;
typedef  TYPE_1__ mp_buffer_info_t ;
struct TYPE_5__ {int /*<<< orphan*/ * read; int /*<<< orphan*/  stream_o; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_BUFFER_READ ; 
 TYPE_3__* MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_call_method_n_kw (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_get_buffer_raise (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_delay_ms (int) ; 
 scalar_t__ mp_obj_is_true (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_new_int (int) ; 
 int /*<<< orphan*/  os_term_dup_obj ; 
 int /*<<< orphan*/  pyb_uart_type ; 
 scalar_t__ telnet_rx_any () ; 
 int telnet_rx_char () ; 
 scalar_t__ uart_rx_any (int /*<<< orphan*/ ) ; 
 int uart_rx_char (int /*<<< orphan*/ ) ; 

int mp_hal_stdin_rx_chr(void) {
    for ( ;; ) {
        // read telnet first
        if (telnet_rx_any()) {
            return telnet_rx_char();
        } else if (MP_STATE_PORT(os_term_dup_obj)) { // then the stdio_dup
            if (mp_obj_is_type(MP_STATE_PORT(os_term_dup_obj)->stream_o, &pyb_uart_type)) {
                if (uart_rx_any(MP_STATE_PORT(os_term_dup_obj)->stream_o)) {
                    return uart_rx_char(MP_STATE_PORT(os_term_dup_obj)->stream_o);
                }
            } else {
                MP_STATE_PORT(os_term_dup_obj)->read[2] = mp_obj_new_int(1);
                mp_obj_t data = mp_call_method_n_kw(1, 0, MP_STATE_PORT(os_term_dup_obj)->read);
                // data len is > 0
                if (mp_obj_is_true(data)) {
                    mp_buffer_info_t bufinfo;
                    mp_get_buffer_raise(data, &bufinfo, MP_BUFFER_READ);
                    return ((int *)(bufinfo.buf))[0];
                }
            }
        }
        mp_hal_delay_ms(1);
    }
}