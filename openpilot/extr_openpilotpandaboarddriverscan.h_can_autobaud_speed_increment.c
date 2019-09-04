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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int AUTOBAUD_SPEEDS_LEN ; 
 size_t BUS_NUM_FROM_CAN_NUM (size_t) ; 
 scalar_t__* can_autobaud_speeds ; 
 scalar_t__* can_speed ; 

void can_autobaud_speed_increment(uint8_t can_number) {
  uint32_t autobaud_speed = can_autobaud_speeds[0];
  uint8_t bus_number = BUS_NUM_FROM_CAN_NUM(can_number);
  for (int i = 0; i < AUTOBAUD_SPEEDS_LEN; i++) {
    if (can_speed[bus_number] == can_autobaud_speeds[i]) {
      if (i+1 < AUTOBAUD_SPEEDS_LEN) {
        autobaud_speed = can_autobaud_speeds[i+1];
      }
      break;
    }
  }
  can_speed[bus_number] = autobaud_speed;
#ifdef DEBUG
  CAN_TypeDef* CAN = CANIF_FROM_CAN_NUM(can_number);
  puts(CAN_NAME_FROM_CANIF(CAN));
  puts(" auto-baud test ");
  putui(can_speed[bus_number]);
  puts(" cbps\n");
#endif
}