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
typedef  int uint8_t ;
struct TYPE_5__ {int* bits; } ;
struct TYPE_6__ {int* keys; TYPE_1__ nkro; } ;
typedef  TYPE_2__ report_keyboard_t ;
struct TYPE_7__ {scalar_t__ nkro; } ;

/* Variables and functions */
 scalar_t__ keyboard_protocol ; 
 TYPE_3__ keymap_config ; 

uint8_t has_anykey(report_keyboard_t* keyboard_report) {
    uint8_t  cnt = 0;
    uint8_t* p   = keyboard_report->keys;
    uint8_t  lp  = sizeof(keyboard_report->keys);
#ifdef NKRO_ENABLE
    if (keyboard_protocol && keymap_config.nkro) {
        p  = keyboard_report->nkro.bits;
        lp = sizeof(keyboard_report->nkro.bits);
    }
#endif
    while (lp--) {
        if (*p++) cnt++;
    }
    return cnt;
}