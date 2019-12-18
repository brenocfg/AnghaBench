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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  LED_DISPLAY ; 
 int NUM_COLS ; 
 int NUM_ROWS ; 
 int /*<<< orphan*/  gdispGGetPixelColor (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void copy_current_led_state(uint8_t* dest) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            dest[i * NUM_COLS + j] = gdispGGetPixelColor(LED_DISPLAY, j, i);
        }
    }
}