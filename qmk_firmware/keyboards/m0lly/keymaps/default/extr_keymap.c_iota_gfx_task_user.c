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
struct CharacterMatrix {int dummy; } ;
typedef  int /*<<< orphan*/  led ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  PSTR (char*) ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_enable ; 
 int /*<<< orphan*/  display ; 
 int host_keyboard_leds () ; 
 char** layer_lookup ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  matrix_clear (struct CharacterMatrix*) ; 
 int /*<<< orphan*/  matrix_update (int /*<<< orphan*/ *,struct CharacterMatrix*) ; 
 int /*<<< orphan*/  matrix_write (struct CharacterMatrix*,char*) ; 
 int /*<<< orphan*/  matrix_write_P (struct CharacterMatrix*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

void iota_gfx_task_user(void) {
  #if DEBUG_TO_SCREEN
    if (debug_enable) {
      return;
    }
  #endif

  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  matrix_write_P(&matrix, PSTR("TKC M0LLY"));

  uint8_t layer = biton32(layer_state);

  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%d", layer);
  matrix_write_P(&matrix, PSTR("\nLayer: "));
  matrix_write(&matrix, layer_lookup[layer]);

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(&matrix, led);
  matrix_update(&display, &matrix);
}