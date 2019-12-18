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
 int /*<<< orphan*/  M0110_INSTANT ; 
 scalar_t__ M0110_NULL ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_hex (scalar_t__) ; 
 scalar_t__ m0110_recv () ; 
 int /*<<< orphan*/  m0110_send (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t instant(void) {
    m0110_send(M0110_INSTANT);
    uint8_t data = m0110_recv();
    if (data != M0110_NULL) {
        debug_hex(data);
        debug(" ");
    }
    return data;
}