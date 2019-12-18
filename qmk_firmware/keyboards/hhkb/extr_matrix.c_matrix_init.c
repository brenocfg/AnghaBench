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
 int /*<<< orphan*/  KEY_INIT () ; 
 size_t MATRIX_ROWS ; 
 int* _matrix0 ; 
 int* _matrix1 ; 
 int debug_enable ; 
 int debug_keyboard ; 
 int* matrix ; 
 int* matrix_prev ; 

void matrix_init(void)
{
#ifdef DEBUG
    debug_enable = true;
    debug_keyboard = true;
#endif

    KEY_INIT();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix = _matrix0;
    matrix_prev = _matrix1;
}