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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 scalar_t__ MATRIX_ROWS ; 
 scalar_t__ bitpop16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_get_row (scalar_t__) ; 

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        count += bitpop16(matrix_get_row(r));
    }
    return count;
}