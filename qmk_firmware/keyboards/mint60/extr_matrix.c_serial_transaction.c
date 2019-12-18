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

/* Variables and functions */
 int ROWS_PER_HAND ; 
 int /*<<< orphan*/  RXLED0 ; 
 int /*<<< orphan*/  RXLED1 ; 
 scalar_t__ isLeftHand ; 
 int /*<<< orphan*/ * matrix ; 
 int /*<<< orphan*/ * serial_slave_buffer ; 
 int serial_update_buffers () ; 

int serial_transaction(void) {
    int slaveOffset = (isLeftHand) ? (ROWS_PER_HAND) : 0;
    int ret=serial_update_buffers();
    if (ret ) {
        if(ret==2)RXLED1;
        return 1;
    }
RXLED0;
    for (int i = 0; i < ROWS_PER_HAND; ++i) {
        matrix[slaveOffset+i] = serial_slave_buffer[i];
    }
    return 0;
}