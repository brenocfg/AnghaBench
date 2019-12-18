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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  bitrev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_get_row (scalar_t__) ; 
 scalar_t__ matrix_rows () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  xprintf (char*,scalar_t__,int /*<<< orphan*/ ) ; 

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        xprintf("%02X: %08b\n", row, bitrev(matrix_get_row(row)));
    }
}