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
 int /*<<< orphan*/  place_bit0 () ; 
 int /*<<< orphan*/  place_bit1 () ; 

__attribute__((used)) static inline void send_byte(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        if (data & (0x80 >> i))
            place_bit1();
        else
            place_bit0();
    }
}