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
 int PBUF_SIZE ; 
 int SREG ; 
 int /*<<< orphan*/  cli () ; 
 int* pbuf ; 
 int pbuf_head ; 
 int pbuf_tail ; 
 int /*<<< orphan*/  print (char*) ; 

__attribute__((used)) static inline void pbuf_enqueue(uint8_t data) {
    uint8_t sreg = SREG;
    cli();
    uint8_t next = (pbuf_head + 1) % PBUF_SIZE;
    if (next != pbuf_tail) {
        pbuf[pbuf_head] = data;
        pbuf_head       = next;
    } else {
        print("pbuf: full\n");
    }
    SREG = sreg;
}