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
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  PAL_MODE_OUTPUT_PUSHPULL ; 
 int /*<<< orphan*/  palClearPad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void select_row(uint8_t row){
  (void)row;
  switch (row) {
    case 0:
      palSetPadMode(GPIOB, 9, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 9);
      break;
    case 1:
      palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 8);
      break;
    case 2:
      palSetPadMode(GPIOB, 7, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 7);
      break;
    case 3:
      palSetPadMode(GPIOB, 6, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 6);
      break;
    case 4:
      palSetPadMode(GPIOB, 5, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 5);
      break;
    case 5:
      palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOA, 4);
      break;
  }
}