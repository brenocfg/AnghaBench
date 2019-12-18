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
struct CharacterMatrix {int dummy; } ;
typedef  int /*<<< orphan*/  led ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  DEVICE_STATE_Addressed 137 
#define  DEVICE_STATE_Configured 136 
#define  DEVICE_STATE_Default 135 
#define  DEVICE_STATE_Powered 134 
#define  DEVICE_STATE_Suspended 133 
#define  DEVICE_STATE_Unattached 132 
#define  L_ADJUST 131 
#define  L_BASE 130 
#define  L_LOWER 129 
#define  L_RAISE 128 
 int /*<<< orphan*/  PSTR (char*) ; 
 int USB_DeviceState ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 scalar_t__ debug_enable ; 
 int /*<<< orphan*/  display ; 
 int host_keyboard_leds () ; 
 int layer_state ; 
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
  matrix_write_P(&matrix, PSTR("USB: "));
#ifdef PROTOCOL_LUFA
  switch (USB_DeviceState) {
    case DEVICE_STATE_Unattached:
      matrix_write_P(&matrix, PSTR("Unattached"));
      break;
    case DEVICE_STATE_Suspended:
      matrix_write_P(&matrix, PSTR("Suspended"));
      break;
    case DEVICE_STATE_Configured:
      matrix_write_P(&matrix, PSTR("Connected"));
      break;
    case DEVICE_STATE_Powered:
      matrix_write_P(&matrix, PSTR("Powered"));
      break;
    case DEVICE_STATE_Default:
      matrix_write_P(&matrix, PSTR("Default"));
      break;
    case DEVICE_STATE_Addressed:
      matrix_write_P(&matrix, PSTR("Addressed"));
      break;
    default:
      matrix_write_P(&matrix, PSTR("Invalid"));
  }
#endif

// Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below

  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(&matrix, PSTR("\n\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(&matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(&matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(&matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
           matrix_write_P(&matrix, PSTR("ADJUST"));
           break;
        default:
           matrix_write(&matrix, buf);
 }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(&matrix, led);
  matrix_update(&display, &matrix);
}