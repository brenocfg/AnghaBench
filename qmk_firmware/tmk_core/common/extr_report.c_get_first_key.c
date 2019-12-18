#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * bits; } ;
struct TYPE_6__ {scalar_t__* keys; TYPE_1__ nkro; } ;
typedef  TYPE_2__ report_keyboard_t ;
struct TYPE_7__ {scalar_t__ nkro; } ;

/* Variables and functions */
 size_t KEYBOARD_REPORT_BITS ; 
 size_t RO_INC (size_t) ; 
 size_t biton (int /*<<< orphan*/ ) ; 
 size_t cb_head ; 
 size_t cb_tail ; 
 scalar_t__ keyboard_protocol ; 
 TYPE_3__ keymap_config ; 

uint8_t get_first_key(report_keyboard_t* keyboard_report) {
#ifdef NKRO_ENABLE
    if (keyboard_protocol && keymap_config.nkro) {
        uint8_t i = 0;
        for (; i < KEYBOARD_REPORT_BITS && !keyboard_report->nkro.bits[i]; i++)
            ;
        return i << 3 | biton(keyboard_report->nkro.bits[i]);
    }
#endif
#ifdef USB_6KRO_ENABLE
    uint8_t i = cb_head;
    do {
        if (keyboard_report->keys[i] != 0) {
            break;
        }
        i = RO_INC(i);
    } while (i != cb_tail);
    return keyboard_report->keys[i];
#else
    return keyboard_report->keys[0];
#endif
}