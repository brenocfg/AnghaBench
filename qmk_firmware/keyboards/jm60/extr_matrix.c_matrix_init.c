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
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  GPIOC ; 
 int /*<<< orphan*/  GPIOD ; 
 int MATRIX_ROWS ; 
 int /*<<< orphan*/  PAL_MODE_INPUT_PULLDOWN ; 
 int /*<<< orphan*/  PAL_MODE_OUTPUT_PUSHPULL ; 
 int /*<<< orphan*/  matrix ; 
 int /*<<< orphan*/  matrix_debouncing ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void matrix_init(void)
{
//debug_matrix = true;
    /* Column(sense) */
    palSetPadMode(GPIOA, 15,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 10,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 11,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 12,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 5,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 6,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 7,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 8,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 9,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 2,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 3,  PAL_MODE_INPUT_PULLDOWN);

    /* Row(strobe) */
    palSetPadMode(GPIOB, 11,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 10,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 2, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 1, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB, 0,  PAL_MODE_OUTPUT_PUSHPULL);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));
}