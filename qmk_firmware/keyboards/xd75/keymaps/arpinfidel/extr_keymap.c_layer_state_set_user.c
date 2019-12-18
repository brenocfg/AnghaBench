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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp100_led_off () ; 
 int /*<<< orphan*/  gp100_led_on () ; 
 int /*<<< orphan*/  gp103_led_off () ; 
 int /*<<< orphan*/  gp103_led_on () ; 

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
    
  gp100_led_off();
  gp103_led_off();
  
  // turns on gp100 (top left led) for odd layers
  if (layer & (1<<0)) gp100_led_on();
  // turns on gp103 (top mid led) for layers 2, 6, ...
  if (layer & (1<<1)) gp103_led_on();
  
  return state;
}