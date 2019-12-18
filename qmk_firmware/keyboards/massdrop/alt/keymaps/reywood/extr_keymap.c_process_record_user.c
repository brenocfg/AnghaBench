#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  ANIMATION_SPEED_STEP ; 
 int /*<<< orphan*/  BREATHE_MIN_STEP ; 
#define  DBG_KBD 146 
#define  DBG_MOU 145 
#define  DBG_MTRX 144 
#define  DBG_TOG 143 
 int /*<<< orphan*/  I2C3733_Control_Set (int) ; 
 scalar_t__ LED_GCR_MAX ; 
 scalar_t__ LED_GCR_STEP ; 
 int /*<<< orphan*/  LED_MODE_MAX_INDEX ; 
 int /*<<< orphan*/  LED_MODE_NORMAL ; 
#define  L_BRD 142 
#define  L_BRI 141 
#define  L_OFF 140 
#define  L_ON 139 
#define  L_PSD 138 
#define  L_PSI 137 
#define  L_PTN 136 
#define  L_PTP 135 
#define  L_T_BR 134 
#define  L_T_MD 133 
#define  L_T_ONF 132 
#define  L_T_PTD 131 
#define  MD_BOOT 130 
 int /*<<< orphan*/  MODS_CTRL ; 
 int /*<<< orphan*/  MODS_SHIFT ; 
 int /*<<< orphan*/  TOGGLE_FLAG_AND_PRINT (int /*<<< orphan*/ ,char*) ; 
#define  U_T_AGCR 129 
#define  U_T_AUTO 128 
 int breathe_dir ; 
 int /*<<< orphan*/  debug_enable ; 
 int /*<<< orphan*/  debug_keyboard ; 
 int /*<<< orphan*/  debug_matrix ; 
 int /*<<< orphan*/  debug_mouse ; 
 scalar_t__ gcr_breathe ; 
 scalar_t__ gcr_desired ; 
 int /*<<< orphan*/  led_animation_breathe_cur ; 
 int led_animation_breathing ; 
 int led_animation_direction ; 
 int /*<<< orphan*/  led_animation_id ; 
 int /*<<< orphan*/  led_animation_speed ; 
 int led_enabled ; 
 int /*<<< orphan*/  led_lighting_mode ; 
 int /*<<< orphan*/  led_setups_count ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  rgb_matrix_record_key_press (TYPE_2__*) ; 
 int timer_elapsed32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read32 () ; 
 int /*<<< orphan*/  usb_extra_manual ; 
 int /*<<< orphan*/  usb_gcr_auto ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint32_t key_timer;

  rgb_matrix_record_key_press(record);

  switch (keycode) {
    case L_BRI:
      if (record->event.pressed) {
        if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
        else gcr_desired += LED_GCR_STEP;
        if (led_animation_breathing) gcr_breathe = gcr_desired;
      }
      return false;
    case L_BRD:
      if (record->event.pressed) {
        if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
        else gcr_desired -= LED_GCR_STEP;
        if (led_animation_breathing) gcr_breathe = gcr_desired;
      }
      return false;
    case L_PTN:
      if (record->event.pressed) {
        if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
        else led_animation_id++;
      }
      return false;
    case L_PTP:
      if (record->event.pressed) {
        if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
        else led_animation_id--;
      }
      return false;
    case L_PSI:
      if (record->event.pressed) {
        led_animation_speed += ANIMATION_SPEED_STEP;
      }
      return false;
    case L_PSD:
      if (record->event.pressed) {
        led_animation_speed -= ANIMATION_SPEED_STEP;
        if (led_animation_speed < 0) led_animation_speed = 0;
      }
      return false;
    case L_T_MD:
      if (record->event.pressed) {
        led_lighting_mode++;
        if (led_lighting_mode > LED_MODE_MAX_INDEX) led_lighting_mode = LED_MODE_NORMAL;
      }
      return false;
    case L_T_ONF:
      if (record->event.pressed) {
        led_enabled = !led_enabled;
        I2C3733_Control_Set(led_enabled);
      }
      return false;
    case L_ON:
      if (record->event.pressed) {
        led_enabled = 1;
        I2C3733_Control_Set(led_enabled);
      }
      return false;
    case L_OFF:
      if (record->event.pressed) {
        led_enabled = 0;
        I2C3733_Control_Set(led_enabled);
      }
      return false;
    case L_T_BR:
      if (record->event.pressed) {
        led_animation_breathing = !led_animation_breathing;
        if (led_animation_breathing) {
          gcr_breathe = gcr_desired;
          led_animation_breathe_cur = BREATHE_MIN_STEP;
          breathe_dir = 1;
        }
      }
      return false;
    case L_T_PTD:
      if (record->event.pressed) {
        led_animation_direction = !led_animation_direction;
      }
      return false;
    case U_T_AUTO:
      if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
        TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
      }
      return false;
    case U_T_AGCR:
      if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
        TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
      }
      return false;
    case DBG_TOG:
      if (record->event.pressed) {
        TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
      }
      return false;
    case DBG_MTRX:
      if (record->event.pressed) {
        TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
      }
      return false;
    case DBG_KBD:
      if (record->event.pressed) {
        TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
      }
      return false;
    case DBG_MOU:
      if (record->event.pressed) {
        TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
      }
      return false;
    case MD_BOOT:
      if (record->event.pressed) {
        key_timer = timer_read32();
      } else {
        if (timer_elapsed32(key_timer) >= 500) {
          reset_keyboard();
        }
      }
      return false;
    default:
      return true; //Process all other keycodes normally
  }
}