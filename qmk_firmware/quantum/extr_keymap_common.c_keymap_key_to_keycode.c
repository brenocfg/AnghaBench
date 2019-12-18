#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {size_t row; size_t col; } ;
typedef  TYPE_1__ keypos_t ;

/* Variables and functions */
 int /*<<< orphan*/ *** keymaps ; 
 int /*<<< orphan*/  pgm_read_word (int /*<<< orphan*/ *) ; 

__attribute__((weak)) uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    // Read entire word (16bits)
    return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
}