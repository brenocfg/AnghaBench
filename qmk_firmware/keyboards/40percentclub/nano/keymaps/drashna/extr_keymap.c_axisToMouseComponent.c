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
typedef  float int8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LSFT ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 float abs (int) ; 
 int axisCoordinate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* keyboard_report ; 
 float maxCursorSpeed ; 
 float precisionSpeed ; 
 float speedRegulator ; 

int8_t axisToMouseComponent(uint8_t pin, int16_t origin, uint8_t maxSpeed, int8_t polarity) {
    int coordinate = axisCoordinate(pin, origin);
    if (coordinate == 0) {
        return 0;
    } else {
        float percent = (float)coordinate / 100;
        if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
            return percent * precisionSpeed * polarity * (abs(coordinate) / speedRegulator);
        } else {
            return percent * maxCursorSpeed * polarity * (abs(coordinate) / speedRegulator);
        }
    }
}