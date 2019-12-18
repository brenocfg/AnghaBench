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

/* Variables and functions */
 size_t MATRIX_ROWS ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  adb_host_init () ; 
 int* matrix ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 

void matrix_init(void)
{
    adb_host_init();

    // wait for keyboard to boot up and receive command
    _delay_ms(2000);

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;
    // print("debug enabled.\n");

    matrix_init_quantum();
}