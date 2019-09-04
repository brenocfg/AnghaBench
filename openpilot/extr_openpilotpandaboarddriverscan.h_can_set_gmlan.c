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

/* Variables and functions */

void can_set_gmlan(int bus) {
  #ifdef PANDA
  if (bus == -1 || bus != can_num_lookup[3]) {
    // GMLAN OFF
    switch (can_num_lookup[3]) {
      case 1:
        puts("disable GMLAN on CAN2\n");
        set_can_mode(1, 0);
        bus_lookup[1] = 1;
        can_num_lookup[1] = 1;
        can_num_lookup[3] = -1;
        can_init(1);
        break;
      case 2:
        puts("disable GMLAN on CAN3\n");
        set_can_mode(2, 0);
        bus_lookup[2] = 2;
        can_num_lookup[2] = 2;
        can_num_lookup[3] = -1;
        can_init(2);
        break;
    }
  }

  if (bus == 1) {
    puts("GMLAN on CAN2\n");
    // GMLAN on CAN2
    set_can_mode(1, 1);
    bus_lookup[1] = 3;
    can_num_lookup[1] = -1;
    can_num_lookup[3] = 1;
    can_init(1);
  } else if (bus == 2 && revision == PANDA_REV_C) {
    puts("GMLAN on CAN3\n");
    // GMLAN on CAN3
    set_can_mode(2, 1);
    bus_lookup[2] = 3;
    can_num_lookup[2] = -1;
    can_num_lookup[3] = 2;
    can_init(2);
  }
  #endif
}