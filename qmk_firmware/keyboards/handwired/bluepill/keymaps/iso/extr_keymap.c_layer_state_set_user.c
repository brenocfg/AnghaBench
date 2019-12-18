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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOA ; 
#define  _FNONE 129 
#define  _FNTWO 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palClearPad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPad (int /*<<< orphan*/ ,int) ; 

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
  case _FNONE:
    palSetPad(GPIOA, 0);  //OFF Color A
    palClearPad(GPIOA, 1); //ON Color B
    break;
  case _FNTWO:
    palClearPad(GPIOA, 0); //ON Color A
    palClearPad(GPIOA, 1);  //ON Color B
    break;
  default: //  for any other layers, or the default layer
    palClearPad(GPIOA, 0); //ON Color A
    palSetPad(GPIOA, 1);  //OFF Color B
    break;
    }
  return state;
}