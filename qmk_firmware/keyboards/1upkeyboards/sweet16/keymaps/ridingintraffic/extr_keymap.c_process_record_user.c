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
typedef  int uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  CLOUD 136 
#define  CMDCLEAR 135 
#define  DISFACE 134 
#define  FU 133 
#define  HAPPYFACE 132 
#define  HEARTFACE 131 
 int /*<<< orphan*/  KC_A ; 
 int /*<<< orphan*/  KC_DEL ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
#define  SHRUG 130 
#define  TFLIP 129 
#define  TFLIP2 128 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_unicode_hex_string (char*) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case CLOUD:       // (っ◕‿◕)っ
                if(record->event.pressed){
                    send_unicode_hex_string("0028 3063 25D5 203F 25D5 0029 3063");
                }
                return false;
                break;
            case FU:       // t(-_-t)
                if(record->event.pressed){
                    SEND_STRING("t(-_-t)");
                }
                return false;
                break;  
            case HAPPYFACE:       // ʘ‿ʘ 
                if(record->event.pressed){
                     send_unicode_hex_string("0298 203F 0298");
                }
                return false;
                break; 
            case CMDCLEAR:
                if (record->event.pressed) {
                    register_code(KC_LGUI);
                    tap_code(KC_A);                 
                    unregister_code(KC_LGUI);
                    tap_code(KC_DEL);                 
                }
                return false;
                break;  
            case SHRUG: // ¯\_(ツ)_/¯
                if (record->event.pressed) {
                    send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
                }
                return false; 
                break;
            case HEARTFACE:       // ♥‿♥
                if(record->event.pressed){
                    send_unicode_hex_string("2665 203F 2665");
                }
                return false;
                break;  
            case DISFACE:       // ಠ_ಠ 
                if(record->event.pressed){
                    send_unicode_hex_string("0CA0 005F 0CA0");
                }
                return false;
                break;
            case TFLIP:         // (╯°□°)╯ ︵ ┻━┻ 
                if(record->event.pressed){
                    send_unicode_hex_string("0028 256F 00B0 25A1 00B0 0029 256F 0020 FE35 0020 253B 2501 253B");
                }
                return false;
                break;
            case TFLIP2:         // ┻━┻︵ \(°□°)/ ︵ ┻━┻  
                if(record->event.pressed){
                    send_unicode_hex_string("253B 2501 253B FE35 0020 005C 0028 00B0 25A1 00B0 0029 002F 0020 FE35 0020 253B 2501 253B");
                }
                return false;
                break;
                } 
    }
    return true;
}