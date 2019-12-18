#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct CharacterMatrix {int dummy; } ;
typedef  int /*<<< orphan*/  led ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int member_0; int member_1; int /*<<< orphan*/  member_2; } ;
struct TYPE_3__ {int member_0; int member_1; int /*<<< orphan*/  member_2; } ;

/* Variables and functions */
#define  L_BASE 130 
 int /*<<< orphan*/  PSTR (char*) ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
#define  _LOWER 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 scalar_t__ get_enable_kc_lang () ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  matrix_write (struct CharacterMatrix*,char*) ; 
 int /*<<< orphan*/  matrix_write_P (struct CharacterMatrix*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3] = {{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  int mode_number = get_enable_kc_lang() ? 0 : 1;
  matrix_write(matrix, logo[mode_number][0]);
  matrix_write(matrix, "\n");
  matrix_write(matrix, logo[mode_number][1]);

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
  switch (biton32(layer_state)) {
    case L_BASE:
      matrix_write_P(matrix, PSTR("Default"));
      break;
    case _RAISE:
      matrix_write_P(matrix, PSTR("Raise"));
      break;
    case _LOWER:
      matrix_write_P(matrix, PSTR("Lower"));
      break;
    default:
      matrix_write(matrix, buf);
  }

  // Host Keyboard LED Status
  char led[40];
  snprintf(led, sizeof(led), "\n%s %s %s",
      (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NMLK" : "    ",
      (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
      (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}