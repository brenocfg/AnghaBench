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
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  rbuf_dequeue () ; 
 int /*<<< orphan*/  rbuf_has_data () ; 

uint8_t ibm4704_recv_response(void) {
    while (!rbuf_has_data()) {
        _delay_ms(1);
    }
    return rbuf_dequeue();
}