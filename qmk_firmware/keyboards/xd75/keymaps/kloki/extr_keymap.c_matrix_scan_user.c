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
 scalar_t__ CTRLDOWN ; 
 scalar_t__ SHIFTDOWN ; 
 scalar_t__ WINDOWN ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case 0:
            rgblight_setrgb(0,240, 255);
            break;
        case 1:
            rgblight_setrgb(0,255, 100);
            break;
        case 2:
            rgblight_setrgb(10,255, 0);
            break;
        case 3:
            rgblight_setrgb(255,0, 85);
            break;
        case 4:
            rgblight_setrgb(240,255, 0);
            break;
        default:
            // none
            break;
    }
    if ( SHIFTDOWN) {
        rgblight_setrgb(255,255, 255);
        }
    if ( CTRLDOWN) {
        rgblight_setrgb(240,255, 0);
        }
    if ( WINDOWN) {
        rgblight_setrgb(255,255, 255);
        }



}