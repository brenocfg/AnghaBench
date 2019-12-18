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
typedef  int /*<<< orphan*/  matrix_row_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  GPIOC ; 
 int /*<<< orphan*/  GPIOD ; 
 int MATRIX_ROWS ; 
 int /*<<< orphan*/  PAL_MODE_INPUT_PULLDOWN ; 
 int /*<<< orphan*/  PAL_MODE_OUTPUT_PUSHPULL ; 
 int /*<<< orphan*/  matrix ; 
 int /*<<< orphan*/  matrix_debouncing ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void matrix_init(void)
{
    /* Column(sense) */
    palSetPadMode(GPIOD, 1,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 7,  PAL_MODE_INPUT_PULLDOWN);

#ifdef INFINITY_LED
    /* Row(strobe) */
    palSetPadMode(GPIOC, 0,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 3,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 4,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 5,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 6,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 7,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 0,  PAL_MODE_OUTPUT_PUSHPULL);
#else
    /* Row(strobe) */
    palSetPadMode(GPIOB, 0,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 3,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 16, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 17, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 4,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC, 5,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 0,  PAL_MODE_OUTPUT_PUSHPULL);
#endif
    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    matrix_init_quantum();
}