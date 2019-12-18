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
 int /*<<< orphan*/  MUX_RCV_BUF_SIZE ; 
 char* rcv_buf ; 
 int /*<<< orphan*/  rcv_head ; 
 int /*<<< orphan*/  rcv_tail ; 

__attribute__((used)) static char rcv_deq(void) {
    char c = 0;
    if (rcv_head != rcv_tail) {
        c = rcv_buf[rcv_tail++];
        rcv_tail %= MUX_RCV_BUF_SIZE;
    }
    return c;
}