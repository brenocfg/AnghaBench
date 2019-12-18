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
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_STRING (char*) ; 
#define  TEST_A1 142 
#define  TEST_A2 141 
#define  TEST_A3 140 
#define  TEST_B1 139 
#define  TEST_B2 138 
#define  TEST_B3 137 
#define  TEST_C1 136 
#define  TEST_C2 135 
#define  TEST_C3 134 
#define  TEST_D1 133 
#define  TEST_D2 132 
#define  TEST_D3 131 
#define  TEST_E1 130 
#define  TEST_E2 129 
#define  TEST_E3 128 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TEST_A1: if(record->event.pressed){ SEND_STRING("A1"); } break;
    case TEST_A2: if(record->event.pressed){ SEND_STRING("A2"); } break;
    case TEST_A3: if(record->event.pressed){ SEND_STRING("A3"); } break;
    case TEST_B1: if(record->event.pressed){ SEND_STRING("B1"); } break;
    case TEST_B2: if(record->event.pressed){ SEND_STRING("B2"); } break;
    case TEST_B3: if(record->event.pressed){ SEND_STRING("B3"); } break;
    case TEST_C1: if(record->event.pressed){ SEND_STRING("C1"); } break;
    case TEST_C2: if(record->event.pressed){ SEND_STRING("C2"); } break;
    case TEST_C3: if(record->event.pressed){ SEND_STRING("C3"); } break;
    case TEST_D1: if(record->event.pressed){ SEND_STRING("D1"); } break;
    case TEST_D2: if(record->event.pressed){ SEND_STRING("D2"); } break;
    case TEST_D3: if(record->event.pressed){ SEND_STRING("D3"); } break;
    case TEST_E1: if(record->event.pressed){ SEND_STRING("E1"); } break;
    case TEST_E2: if(record->event.pressed){ SEND_STRING("E2"); } break;
    case TEST_E3: if(record->event.pressed){ SEND_STRING("E3"); } break;
  }
  return true;
}