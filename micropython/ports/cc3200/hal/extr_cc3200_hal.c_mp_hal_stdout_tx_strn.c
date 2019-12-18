#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_2__ {int /*<<< orphan*/ * write; int /*<<< orphan*/  stream_o; } ;

/* Variables and functions */
 TYPE_1__* MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_call_method_n_kw (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_new_str_of_type (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  mp_type_str ; 
 int /*<<< orphan*/  os_term_dup_obj ; 
 int /*<<< orphan*/  pyb_uart_type ; 
 int /*<<< orphan*/  telnet_tx_strn (char const*,size_t) ; 
 int /*<<< orphan*/  uart_tx_strn (int /*<<< orphan*/ ,char const*,size_t) ; 

void mp_hal_stdout_tx_strn(const char *str, size_t len) {
    if (MP_STATE_PORT(os_term_dup_obj)) {
        if (mp_obj_is_type(MP_STATE_PORT(os_term_dup_obj)->stream_o, &pyb_uart_type)) {
            uart_tx_strn(MP_STATE_PORT(os_term_dup_obj)->stream_o, str, len);
        } else {
            MP_STATE_PORT(os_term_dup_obj)->write[2] = mp_obj_new_str_of_type(&mp_type_str, (const byte *)str, len);
            mp_call_method_n_kw(1, 0, MP_STATE_PORT(os_term_dup_obj)->write);
        }
    }
    // and also to telnet
    telnet_tx_strn(str, len);
}