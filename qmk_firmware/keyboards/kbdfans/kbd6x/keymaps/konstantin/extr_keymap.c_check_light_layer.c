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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ IS_HOST_LED_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_LAYER_ON_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L_FN ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  caps_light () ; 
 int /*<<< orphan*/  fn_light () ; 
 int /*<<< orphan*/  restore_light () ; 

__attribute__((used)) static void check_light_layer(uint32_t state) {
    if (IS_LAYER_ON_STATE(state, L_FN)) {
        fn_light();
    } else if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        caps_light();
    } else {
        restore_light();
    }
}