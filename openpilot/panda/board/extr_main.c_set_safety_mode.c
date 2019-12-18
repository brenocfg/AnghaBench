#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_can_mode ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CAN_LIVE ; 
 int /*<<< orphan*/  ALL_CAN_SILENT ; 
 int /*<<< orphan*/  CAN_MODE_NORMAL ; 
 int /*<<< orphan*/  CAN_MODE_OBD_CAN2 ; 
#define  SAFETY_ELM327 129 
#define  SAFETY_NOOUTPUT 128 
 int /*<<< orphan*/  board_has_obd () ; 
 int /*<<< orphan*/  can_init_all () ; 
 int /*<<< orphan*/  can_silent ; 
 TYPE_1__* current_board ; 
 unsigned int heartbeat_counter ; 
 int /*<<< orphan*/  puts (char*) ; 
 int safety_set_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_intercept_relay (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

void set_safety_mode(uint16_t mode, int16_t param) {
  int err = safety_set_mode(mode, param);
  if (err == -1) {
    puts("Error: safety set mode failed\n");
  } else {
    switch (mode) {
        case SAFETY_NOOUTPUT:
          set_intercept_relay(false);
          if(board_has_obd()){
            current_board->set_can_mode(CAN_MODE_NORMAL);
          }
          can_silent = ALL_CAN_SILENT;
          break;
        case SAFETY_ELM327:
          set_intercept_relay(false);
          heartbeat_counter = 0U;
          if(board_has_obd()){
            current_board->set_can_mode(CAN_MODE_OBD_CAN2);
          }
          can_silent = ALL_CAN_LIVE;
          break;
        default:
          set_intercept_relay(true);
          heartbeat_counter = 0U;
          if(board_has_obd()){
            current_board->set_can_mode(CAN_MODE_NORMAL);
          }
          can_silent = ALL_CAN_LIVE;
          break;
      }
    can_init_all();
  }
}