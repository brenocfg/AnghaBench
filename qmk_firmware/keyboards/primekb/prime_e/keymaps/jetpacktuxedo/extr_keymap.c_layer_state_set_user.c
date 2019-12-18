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
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAPS_LED_PIN ; 
 int /*<<< orphan*/  NUM_LED_PIN ; 
 int /*<<< orphan*/  SCROLL_LED_PIN ; 
 scalar_t__ layer_state_cmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, 1)) {
        writePinHigh(CAPS_LED_PIN);
    } else {
        writePinLow(CAPS_LED_PIN);
    }
    if (layer_state_cmp(state, 2)) {
        writePinHigh(NUM_LED_PIN);
    } else {
        writePinLow(NUM_LED_PIN);
    }
    if (layer_state_cmp(state, 3)) {
        writePinHigh(SCROLL_LED_PIN);
    } else {
        writePinLow(SCROLL_LED_PIN);
    }
    return state;
}