#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_6__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_2__ event; } ;
typedef  TYPE_1__ keyrecord_t ;
typedef  TYPE_2__ keyevent_t ;
struct TYPE_7__ {int swap_lalt_lgui; int swap_ralt_rgui; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 int ENT ; 
 int EQL ; 
 int /*<<< orphan*/  LALT ; 
 int LBRC ; 
 int /*<<< orphan*/  LCTRL ; 
 int LEFT ; 
 int /*<<< orphan*/  LGUI ; 
 int /*<<< orphan*/  LSFT ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int MINS ; 
#define  M_BACK 137 
#define  M_ENTR 136 
#define  M_FWRD 135 
#define  M_NSPC 134 
#define  M_NTAB 133 
#define  M_PSPC 132 
#define  M_PTAB 131 
#define  M_SCRN 130 
#define  M_ZOIN 129 
#define  M_ZOUT 128 
 int PSCR ; 
 int RBRC ; 
 int RIGHT ; 
 int /*<<< orphan*/  RSFT ; 
 int /*<<< orphan*/  T (int) ; 
 int TAB ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 TYPE_3__ keymap_config ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  keyevent_t event = record->event;

  if (!eeconfig_is_enabled()) {
    eeconfig_init();
  }
  bool use_cmd = true;    // Use, for example, Cmd-Tab, Cmd-C, Cmd-V, etc.
  // Compare to MAGIC_SWAP_ALT_GUI and MAGIC_UNSWAP_ALT_GUI configs, set in:
  // quantum/quantum.c
  if(keymap_config.swap_lalt_lgui == 1 && keymap_config.swap_ralt_rgui == 1) {
    use_cmd = false;      // ... or, Alt-Tab, Ctrl-C, Ctrl-V, etc.
  }
    switch(id) {
      case M_BACK:
          /* Command + [ or previous page */
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LGUI), T(LBRC), U(LGUI), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LALT), T(LEFT), U(LALT), END ) : MACRO(END));
          }
      case M_FWRD:
          /* Command + ] or next page */
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LGUI), T(RBRC), U(LGUI), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LALT), T(RIGHT), U(LALT), END ) : MACRO(END));
          }
      case M_PTAB:
          /* Command + { or prev tab. */
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LGUI), D(RSFT), T(LBRC), U(RSFT), U(LGUI), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LCTRL), D(RSFT), T(TAB), U(RSFT), U(LCTRL), END ) : MACRO(END));
          }
      case M_NTAB:
          /* Command + } or next tab*/
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LGUI), D(RSFT), T(RBRC), U(RSFT), U(LGUI), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LCTRL), T(TAB), U(LCTRL), END ) : MACRO(END));
          }
      case M_ZOUT:
          /* Command + - or Ctrl + -*/
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LGUI), T(MINS), U(LGUI), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LCTRL), T(MINS), U(LCTRL), END ) : MACRO(END));
          }
          break;
      case M_ZOIN:
          /* Command + = or Ctrl + =*/
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LGUI), T(EQL), U(LGUI), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LCTRL), T(EQL), U(LCTRL), END ) : MACRO(END));
          }
          break;
      case M_ENTR:
          /* Command + Enter or Ctrl + Enter*/
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LGUI), T(ENT), U(LGUI), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LCTRL), T(ENT), U(LCTRL), END ) : MACRO(END));
          }
      case M_SCRN:
          /* Command + Enter or Ctrl + Enter*/
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LGUI), D(LCTRL), D(LSFT), T(4), U(LSFT), U(LGUI), U(LCTRL), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( T(PSCR) ) : MACRO(END));
          }
      case M_NSPC:
          /* Next space / desktop */
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LCTRL), T(RIGHT), U(LCTRL), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LGUI), T(RIGHT), U(LGUI), END ) : MACRO(END));
          }
          break;
      case M_PSPC:
          /* Previous space / desktop */
          if (use_cmd) {
              return (event.pressed ? MACRO( D(LCTRL), T(LEFT), U(LCTRL), END ) : MACRO(END));
          } else {
              return (event.pressed ? MACRO( D(LGUI), T(LEFT), U(LGUI), END ) : MACRO(END));
          }
        default:
            break;
    }
  return MACRO_NONE;
}