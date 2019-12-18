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

/* Variables and functions */
 int /*<<< orphan*/  PSTR (char*) ; 
#define  _ADJUST 132 
#define  _GAME 131 
#define  _LOWER 130 
#define  _QWERTY 129 
#define  _RAISE 128 
 int biton (scalar_t__) ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_state ; 
 scalar_t__ layer_state ; 
 int /*<<< orphan*/  oled_write_P (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void render_layer(void)
{
    uint8_t layer = layer_state ? biton(layer_state) : biton32(default_layer_state);
#ifdef OLED_90ROTATION
    oled_write_P(PSTR("Layer"), false);
#else
    oled_write_P(PSTR("Layer: "), false);
#endif

    switch (layer)
    {
        case _QWERTY:
            oled_write_P(PSTR("BASE "), false);
            break;
#ifndef GAMELAYER_DISABLE
        case _GAME:
            oled_write_P(PSTR("GAME "), false);
            break;
#endif
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE"), false);
            break;
#ifdef TRILAYER_ENABLED
        case _ADJUST:
            oled_write_P(PSTR("ADJST"), false);
            break;
#endif
    }
}