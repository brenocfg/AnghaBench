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
 int /*<<< orphan*/  SREG ; 
 int /*<<< orphan*/  cli () ; 
 scalar_t__ pbuf_head ; 
 scalar_t__ pbuf_tail ; 

__attribute__((used)) static inline bool pbuf_has_data(void) {
    uint8_t sreg = SREG;
    cli();
    bool has_data = (pbuf_head != pbuf_tail);
    SREG          = sreg;
    return has_data;
}