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
typedef  int /*<<< orphan*/  macro_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  KC_T ; 
 int /*<<< orphan*/  const* MACRODOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  TYPE (int /*<<< orphan*/ ) ; 

const macro_t * action_get_macro(keyrecord_t * record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch (id) {
    case 0:
      return MACRODOWN(TYPE(KC_T), END);
      break;
  }
  return MACRO_NONE;
}