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
 int /*<<< orphan*/  KC_1 ; 
 int /*<<< orphan*/  KC_2 ; 
 int /*<<< orphan*/  KC_3 ; 
 int /*<<< orphan*/  KC_4 ; 
 scalar_t__ _DIABLO ; 
 scalar_t__ biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  tap (int /*<<< orphan*/ ) ; 

void send_diablo_keystroke(uint8_t diablo_key) {
  if (biton32(layer_state) == _DIABLO) {
    switch (diablo_key) {
      case 0:
        tap(KC_1); break;
      case 1:
        tap(KC_2); break;
      case 2:
        tap(KC_3); break;
      case 3:
        tap(KC_4); break;
    }
  }
}