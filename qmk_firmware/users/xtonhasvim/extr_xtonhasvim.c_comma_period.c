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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_LBRACKET ; 
 int /*<<< orphan*/  KC_RBRACKET ; 
 int /*<<< orphan*/  KC_SLASH ; 
 int /*<<< orphan*/  SHIFTED ; 
#define  VIM_COMMA 129 
#define  VIM_PERIOD 128 

__attribute__((used)) static void comma_period(uint16_t keycode) {
  switch (keycode) {
  case VIM_COMMA:
    if (SHIFTED) {
      // indent
      CMD(KC_LBRACKET);
    } else {
      // toggle comment
      CMD(KC_SLASH);
    }
    break;
  case VIM_PERIOD:
    if (SHIFTED) {
      // outdent
      CMD(KC_RBRACKET);
    }
    break;
  }
}