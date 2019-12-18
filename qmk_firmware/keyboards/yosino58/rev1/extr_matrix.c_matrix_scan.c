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
 int ROWS_PER_HAND ; 
 int /*<<< orphan*/  SERIAL_MASTER_BUFFER_LENGTH ; 
 scalar_t__ isLeftHand ; 
 scalar_t__ is_master ; 
 int /*<<< orphan*/ * matrix ; 
 int /*<<< orphan*/  matrix_master_scan () ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  matrix_slave_scan () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ serial_master_buffer ; 

uint8_t matrix_scan(void)
{
    if (is_master) {
        matrix_master_scan();
    }else{
        matrix_slave_scan();
        int offset = (isLeftHand) ? ROWS_PER_HAND : 0;
        memcpy(&matrix[offset],
               (void *)serial_master_buffer, SERIAL_MASTER_BUFFER_LENGTH);
        matrix_scan_quantum();
    }
    return 1;
}