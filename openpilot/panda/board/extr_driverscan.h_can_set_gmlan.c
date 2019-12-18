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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_can_mode ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_MODE_GMLAN_CAN2 ; 
 int /*<<< orphan*/  CAN_MODE_GMLAN_CAN3 ; 
 int /*<<< orphan*/  CAN_MODE_NORMAL ; 
 scalar_t__ board_has_gmlan () ; 
 int* bus_lookup ; 
 int /*<<< orphan*/  can_init (int) ; 
 int* can_num_lookup ; 
 TYPE_1__* current_board ; 
 int /*<<< orphan*/  puth (int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void can_set_gmlan(uint8_t bus) {
  if(board_has_gmlan()){
    // first, disable GMLAN on prev bus
    uint8_t prev_bus = can_num_lookup[3];
    if (bus != prev_bus) {
      switch (prev_bus) {
        case 1:
        case 2:
          puts("Disable GMLAN on CAN");
          puth(prev_bus + 1U);
          puts("\n");
          current_board->set_can_mode(CAN_MODE_NORMAL);
          bus_lookup[prev_bus] = prev_bus;
          can_num_lookup[prev_bus] = prev_bus;
          can_num_lookup[3] = -1;
          can_init(prev_bus);
          break;
        default:
          // GMLAN was not set on either BUS 1 or 2
          break;
      }
    }

    // now enable GMLAN on the new bus
    switch (bus) {
      case 1:
      case 2:
        puts("Enable GMLAN on CAN");
        puth(bus + 1U);
        puts("\n");
        current_board->set_can_mode((bus == 1U) ? CAN_MODE_GMLAN_CAN2 : CAN_MODE_GMLAN_CAN3);
        bus_lookup[bus] = 3;
        can_num_lookup[bus] = -1;
        can_num_lookup[3] = bus;
        can_init(bus);
        break;
      case 0xFF:  //-1 unsigned
        break;
      default:
        puts("GMLAN can only be set on CAN2 or CAN3\n");
        break;
    }
  } else {
    puts("GMLAN not available on black panda\n");
  }
}