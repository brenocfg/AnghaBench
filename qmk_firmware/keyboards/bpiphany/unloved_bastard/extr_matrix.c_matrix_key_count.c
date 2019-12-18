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
 scalar_t__ bitpop32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * matrix ; 

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++)
        count += bitpop32(matrix[row]);
    return count;
}