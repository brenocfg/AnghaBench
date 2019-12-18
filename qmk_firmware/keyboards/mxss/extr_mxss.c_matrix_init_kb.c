#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_3__ {scalar_t__ mode; int val; int /*<<< orphan*/  raw; } ;
typedef  TYPE_1__ fled_config ;
struct TYPE_4__ {scalar_t__ hue; int /*<<< orphan*/  sat; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_FRONTLED_ADDR ; 
 scalar_t__ FLED_CAPS_H ; 
 int /*<<< orphan*/  FLED_CAPS_S ; 
 scalar_t__ FLED_INDI ; 
 scalar_t__ FLED_RGB ; 
 int FLED_VAL_STEP ; 
 int USB_LED_CAPS_LOCK ; 
 size_t biton32 (int /*<<< orphan*/ ) ; 
 scalar_t__ eeprom_is_valid () ; 
 int /*<<< orphan*/  eeprom_read_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_update_conf () ; 
 scalar_t__ fled_mode ; 
 int fled_val ; 
 int /*<<< orphan*/ * fleds ; 
 int host_keyboard_leds () ; 
 TYPE_2__* layer_colors ; 
 int /*<<< orphan*/  layer_state ; 
 size_t lc_size ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  sethsv (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setrgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void matrix_init_kb(void) {
    // If EEPROM config exists, load it
    if (eeprom_is_valid()) {
        fled_config fled_conf;
        fled_conf.raw = eeprom_read_byte(EEPROM_FRONTLED_ADDR);
        fled_mode = fled_conf.mode;
        fled_val = fled_conf.val * FLED_VAL_STEP;
    // Else, default config
    } else {
        fled_mode = FLED_RGB;
        fled_val = 10 * FLED_VAL_STEP;
        eeprom_update_conf();   // Store default config to EEPROM
    }
    
    // Set default values for leds
    setrgb(0, 0, 0, &fleds[0]);
    setrgb(0, 0, 0, &fleds[1]);
    
    // Handle lighting for indicator mode
    if (fled_mode == FLED_INDI) {
        // Enable capslock led if enabled on host
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))
            sethsv(FLED_CAPS_H, FLED_CAPS_S, fled_val, &fleds[0]);
        
        // Determine and set colour of layer LED according to current layer
        // if hue = sat = 0, leave LED off
        uint8_t layer = biton32(layer_state);
        if (layer < lc_size && !(layer_colors[layer].hue == 0 && layer_colors[layer].hue == 0))
            sethsv(layer_colors[layer].hue, layer_colors[layer].sat, fled_val, &fleds[1]);
    }

	matrix_init_user();
}