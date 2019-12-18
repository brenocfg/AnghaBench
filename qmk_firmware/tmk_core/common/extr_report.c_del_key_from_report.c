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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  report_keyboard_t ;
struct TYPE_2__ {scalar_t__ nkro; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_key_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_key_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ keyboard_protocol ; 
 TYPE_1__ keymap_config ; 

void del_key_from_report(report_keyboard_t* keyboard_report, uint8_t key) {
#ifdef NKRO_ENABLE
    if (keyboard_protocol && keymap_config.nkro) {
        del_key_bit(keyboard_report, key);
        return;
    }
#endif
    del_key_byte(keyboard_report, key);
}