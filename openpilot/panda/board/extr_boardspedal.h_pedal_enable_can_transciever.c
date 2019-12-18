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

/* Variables and functions */
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  puth (int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  set_gpio_output (int /*<<< orphan*/ ,int,int) ; 

void pedal_enable_can_transciever(uint8_t transciever, bool enabled) {
  switch (transciever){
    case 1:
      set_gpio_output(GPIOB, 3, !enabled);
      break;
    default:
      puts("Invalid CAN transciever ("); puth(transciever); puts("): enabling failed\n");
      break;
  }
}