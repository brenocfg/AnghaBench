#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  C ; 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  ESC ; 
 int /*<<< orphan*/  LCTRL ; 
 int /*<<< orphan*/  LGUI ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
#define  MACRO_OSX_COPY 131 
#define  MACRO_OSX_PASTE 130 
#define  MACRO_TMUX_ESC 129 
#define  MACRO_TMUX_PASTE 128 
 int /*<<< orphan*/  P ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case MACRO_TMUX_ESC:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), T(A), U(LCTRL), D(ESC), END);
      }
      return MACRO(U(ESC), END);
    case MACRO_TMUX_PASTE:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), T(A), U(LCTRL), D(P), END);
      }
      return MACRO(U(P), END);
    case MACRO_OSX_COPY:
      if (record->event.pressed) {
        return MACRO(D(LGUI), D(C), END);
      }
      return MACRO(U(C), U(LGUI), END);
    case MACRO_OSX_PASTE:
      if (record->event.pressed) {
        return MACRO(D(LGUI), D(V), END);
      }
      return MACRO(U(V), U(LGUI), END);
  }
  return MACRO_NONE;
}