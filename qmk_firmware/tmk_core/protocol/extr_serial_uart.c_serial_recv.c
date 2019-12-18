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

/* Variables and functions */
 size_t RBUF_SIZE ; 
 int /*<<< orphan*/ * rbuf ; 
 int /*<<< orphan*/  rbuf_check_rts_lo () ; 
 size_t rbuf_head ; 
 size_t rbuf_tail ; 

uint8_t serial_recv(void) {
    uint8_t data = 0;
    if (rbuf_head == rbuf_tail) {
        return 0;
    }

    data      = rbuf[rbuf_tail];
    rbuf_tail = (rbuf_tail + 1) % RBUF_SIZE;
    rbuf_check_rts_lo();
    return data;
}