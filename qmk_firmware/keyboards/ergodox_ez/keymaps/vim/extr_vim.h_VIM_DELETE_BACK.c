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
 int /*<<< orphan*/  KC_DEL ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LEFT ; 
 int /*<<< orphan*/  KC_LSHIFT ; 
 int /*<<< orphan*/  KC_NO ; 
 int /*<<< orphan*/  PRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIM_LEADER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 

void VIM_DELETE_BACK(void) {
  print("\e[31mb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    SHIFT(KC_LEFT); // select to start of word
    SHIFT(KC_DEL); // delete selection
  RELEASE(KC_LSHIFT);
}