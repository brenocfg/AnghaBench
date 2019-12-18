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

/* Variables and functions */
 int /*<<< orphan*/  CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_NO ; 
 int /*<<< orphan*/  KC_RIGHT ; 
 int /*<<< orphan*/  KC_X ; 
 int /*<<< orphan*/  PRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIM_LEADER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 

void VIM_DELETE_END(void) {
  print("\e[31me\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LALT);
  CMD(KC_X);
}