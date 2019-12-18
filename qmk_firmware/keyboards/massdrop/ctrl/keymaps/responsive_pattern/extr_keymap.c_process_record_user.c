#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_9__ {int alive; int led_id; void* time; } ;
struct TYPE_8__ {int PATTERN_INDEX; int TRAVEL_DISTANCE; int COLOR_PATTERN_INDEX; int WAVE_PERIOD; int WAVE_FRONT_WIDTH; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANIMATION_SPEED_STEP ; 
 int /*<<< orphan*/  BREATHE_MIN_STEP ; 
 int COLOR_PATTERNS_COUNT ; 
#define  DBG_KBD 154 
#define  DBG_MOU 153 
#define  DBG_MTRX 152 
#define  DBG_TOG 151 
 int /*<<< orphan*/  I2C3733_Control_Set (int) ; 
 TYPE_5__* KEY_STROKES ; 
 int KEY_STROKES_LENGTH ; 
 scalar_t__ LED_GCR_MAX ; 
 scalar_t__ LED_GCR_STEP ; 
 int /*<<< orphan*/  LED_MODE_MAX_INDEX ; 
 int /*<<< orphan*/  LED_MODE_NORMAL ; 
#define  L_BRD 150 
#define  L_BRI 149 
#define  L_CP_NX 148 
#define  L_CP_PR 147 
#define  L_OFF 146 
#define  L_ON 145 
#define  L_PSD 144 
#define  L_PSI 143 
#define  L_PTN 142 
#define  L_PTP 141 
#define  L_SP_FA 140 
#define  L_SP_NE 139 
#define  L_SP_NW 138 
#define  L_SP_PR 137 
#define  L_SP_SL 136 
#define  L_SP_WD 135 
#define  L_T_BR 134 
#define  L_T_MD 133 
#define  L_T_ONF 132 
#define  L_T_PTD 131 
#define  MD_BOOT 130 
 int /*<<< orphan*/  MODS_CTRL ; 
 int /*<<< orphan*/  MODS_SHIFT ; 
 int PATTERN_COUNT ; 
 int /*<<< orphan*/  TOGGLE_FLAG_AND_PRINT (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ USER_CONFIG ; 
#define  U_T_AGCR 129 
#define  U_T_AUTO 128 
 int breathe_dir ; 
 int /*<<< orphan*/  debug_enable ; 
 int /*<<< orphan*/  debug_keyboard ; 
 int /*<<< orphan*/  debug_matrix ; 
 int /*<<< orphan*/  debug_mouse ; 
 scalar_t__ gcr_breathe ; 
 scalar_t__ gcr_desired ; 
 int ktli (int) ; 
 int /*<<< orphan*/  led_animation_breathe_cur ; 
 int led_animation_breathing ; 
 int led_animation_direction ; 
 int /*<<< orphan*/  led_animation_id ; 
 int /*<<< orphan*/  led_animation_speed ; 
 int led_enabled ; 
 int /*<<< orphan*/  led_lighting_mode ; 
 int /*<<< orphan*/  led_setups_count ; 
 int /*<<< orphan*/  refresh_color_pattern_indicators () ; 
 int /*<<< orphan*/  refresh_pattern_indicators () ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int timer_elapsed32 (void*) ; 
 void* timer_read32 () ; 
 int /*<<< orphan*/  usb_extra_manual ; 
 int /*<<< orphan*/  usb_gcr_auto ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;


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

















        case L_SP_PR: // previous dripple pattern
        case L_SP_NE: // next dripple pattern
            if (record->event.pressed) {
#define PATTERN_COUNT 7
                uint8_t incre = keycode == L_SP_PR ? PATTERN_COUNT-1 : 1;
                USER_CONFIG.PATTERN_INDEX += incre;
                USER_CONFIG.PATTERN_INDEX %= PATTERN_COUNT;

                if(USER_CONFIG.PATTERN_INDEX <= 4){
                    USER_CONFIG.TRAVEL_DISTANCE = 25;
                    USER_CONFIG.COLOR_PATTERN_INDEX = 0;
                    USER_CONFIG.WAVE_PERIOD = 50;
                }

                switch(USER_CONFIG.PATTERN_INDEX){
                case 0: // None
                    break;
                case 1: // background off, wave on
                    USER_CONFIG.WAVE_FRONT_WIDTH = 2;
                    break;
                case 2: // background on, wave off
                    USER_CONFIG.WAVE_FRONT_WIDTH = 5;
                    break;
                case 3: // background off, rainbow wave
                    USER_CONFIG.WAVE_FRONT_WIDTH = 10;
                    break;
                case 4: // background on, rainbow wave
                    USER_CONFIG.WAVE_FRONT_WIDTH = 10;
                    break;
                case 5:
                    USER_CONFIG.WAVE_FRONT_WIDTH = 10;

                    USER_CONFIG.COLOR_PATTERN_INDEX = 2;
                    USER_CONFIG.TRAVEL_DISTANCE = 0;
                    USER_CONFIG.WAVE_PERIOD = 100;
                    break;
                case 6:
                    USER_CONFIG.WAVE_FRONT_WIDTH = 25;

                    USER_CONFIG.COLOR_PATTERN_INDEX = 3;
                    USER_CONFIG.TRAVEL_DISTANCE = 2;
                    USER_CONFIG.WAVE_PERIOD = 10;
                    break;
                }

                // remove effect after changing pattern
                for(int i = 0; i < KEY_STROKES_LENGTH; ++i){
                    KEY_STROKES[i].alive = 0;
                }
                refresh_pattern_indicators();
                refresh_color_pattern_indicators();
            }
            return false;
        case L_SP_WD:
        case L_SP_NW:
            if(record->event.pressed){
                short incre = keycode == L_SP_WD ? 1 : -1;
                USER_CONFIG.WAVE_FRONT_WIDTH += incre;
                if(USER_CONFIG.WAVE_FRONT_WIDTH < 1){
                    USER_CONFIG.WAVE_FRONT_WIDTH = 1;
                }
            }
            return false;
        case L_SP_FA:
        case L_SP_SL:
            if(record->event.pressed){
                short incre = keycode == L_SP_FA ? -1 : 1;

                USER_CONFIG.WAVE_PERIOD += 10 * incre;
                if(USER_CONFIG.WAVE_PERIOD < 10){
                    USER_CONFIG.WAVE_PERIOD = 10;
                }
            }
            return false;
        // these are the keys not in range 0x04 - 0x52
        case L_CP_PR:
        case L_CP_NX:
            if(record->event.pressed){
                uint8_t incre = keycode == L_CP_PR ? COLOR_PATTERNS_COUNT - 1 : 1;
                USER_CONFIG.COLOR_PATTERN_INDEX += incre;
                USER_CONFIG.COLOR_PATTERN_INDEX %= COLOR_PATTERNS_COUNT;
                refresh_color_pattern_indicators();
            }
            return false;
        default:
            if (record->event.pressed){
                uint8_t led_id = ktli(keycode);
                if(led_id){
                    for(int i = 0; i < KEY_STROKES_LENGTH; ++i){
                        if(!KEY_STROKES[i].alive){
                            KEY_STROKES[i].alive = 1;
                            KEY_STROKES[i].led_id = led_id;
                            KEY_STROKES[i].time = timer_read32();
                            break;
                        }
                    }
                }
            }
            return true; //Process all other keycodes normally
    }
}