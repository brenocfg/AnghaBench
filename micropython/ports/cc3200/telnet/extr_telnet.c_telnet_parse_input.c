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
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ E_TELNET_STE_LOGGED_IN ; 
 int MIN (int,int) ; 
 int mp_interrupt_char ; 
 int /*<<< orphan*/  mp_keyboard_interrupt () ; 
 TYPE_1__ telnet_data ; 

__attribute__((used)) static void telnet_parse_input (uint8_t *str, int16_t *len) {
    int16_t b_len = *len;
    uint8_t *b_str = str;

    for (uint8_t *_str = b_str; _str < b_str + b_len; ) {
        if (*_str <= 127) {
            if (telnet_data.state == E_TELNET_STE_LOGGED_IN && *_str == mp_interrupt_char) {
                // raise a keyboard exception
                mp_keyboard_interrupt();
                (*len)--;
                _str++;
            }
            else if (*_str > 0) {
                *str++ = *_str++;
            }
            else {
                _str++;
                *len -= 1;
            }
        }
        else {
            // in case we have received an incomplete telnet option, unlikely, but possible
            _str += MIN(3, *len);
            *len -= MIN(3, *len);
        }
    }
}