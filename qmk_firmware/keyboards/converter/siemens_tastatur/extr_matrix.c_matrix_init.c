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
 int /*<<< orphan*/  A0 ; 
 int /*<<< orphan*/  A1 ; 
 int /*<<< orphan*/  A10 ; 
 int /*<<< orphan*/  A2 ; 
 int /*<<< orphan*/  A3 ; 
 int /*<<< orphan*/  A4 ; 
 int /*<<< orphan*/  A5 ; 
 int /*<<< orphan*/  A6 ; 
 int /*<<< orphan*/  A7 ; 
 int /*<<< orphan*/  A8 ; 
 int /*<<< orphan*/  A9 ; 
 int /*<<< orphan*/  B11 ; 
 int /*<<< orphan*/  B12 ; 
 int /*<<< orphan*/  B13 ; 
 int /*<<< orphan*/  B14 ; 
 int /*<<< orphan*/  B15 ; 
 int /*<<< orphan*/  B3 ; 
 int /*<<< orphan*/  B4 ; 
 int /*<<< orphan*/  B5 ; 
 int /*<<< orphan*/  B6 ; 
 int /*<<< orphan*/  B7 ; 
 int /*<<< orphan*/  B8 ; 
 int /*<<< orphan*/  B9 ; 
 int /*<<< orphan*/  EXTD1 ; 
 int MATRIX_ROWS ; 
 int /*<<< orphan*/  extStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extcfg ; 
 int /*<<< orphan*/  matrix ; 
 int /*<<< orphan*/  matrix_debouncing ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setPinInputHigh (int /*<<< orphan*/ ) ; 

void matrix_init(void) {
    //Set I/O as pull-up inputs to read states
    setPinInputHigh(A0);
    setPinInputHigh(A1);
    setPinInputHigh(A2);
    setPinInputHigh(A3);
    setPinInputHigh(A4);
    setPinInputHigh(A5);
    setPinInputHigh(A6);
    setPinInputHigh(A7);
    setPinInputHigh(A8);
    setPinInputHigh(A9);
    setPinInputHigh(A10);
    setPinInputHigh(B3);
    setPinInputHigh(B4);
    setPinInputHigh(B5);
    setPinInputHigh(B6);
    setPinInputHigh(B7);
    setPinInputHigh(B8);
    setPinInputHigh(B9);
    setPinInputHigh(B11);
    setPinInputHigh(B12);
    setPinInputHigh(B13);
    setPinInputHigh(B14);
    setPinInputHigh(B15);

    memset(matrix, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(matrix_debouncing, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    matrix_init_quantum();
    //Start interrupt driver
    extStart(&EXTD1, &extcfg);
}