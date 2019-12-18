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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOB ; 
#define  _ADJUST 130 
#define  _LOWER 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palClearPad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_tri_layer_state (int /*<<< orphan*/ ,int const,int const,int const) ; 

uint32_t layer_state_set_user(uint32_t state) {
    palClearPad(GPIOB, 8);
    palClearPad(GPIOB, 9);
    uint8_t layer = biton32(state);
    switch (layer) {
        case _LOWER:
            palSetPad(GPIOB, 9);
            break;
        case _RAISE:
            palSetPad(GPIOB, 8);
            break;
        case _ADJUST:
            palSetPad(GPIOB, 9);
            palSetPad(GPIOB, 8);
            break;
        default:
            break;
    }
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}