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

__attribute__((used)) static size_t _find_emulation_prevention_byte(const uint8_t* data, size_t size)
{
    size_t offset = 2;

    while (offset < size) {
        if (0 == data[offset]) {
            // 0 0 X 3 //; we know X is zero
            offset += 1;
        } else if (3 != data[offset]) {
            // 0 0 X 0 0 3; we know X is not 0 and not 3
            offset += 3;
        } else if (0 != data[offset - 1]) {
            // 0 X 0 0 3
            offset += 2;
        } else if (0 != data[offset - 2]) {
            // X 0 0 3
            offset += 1;
        } else {
            // 0 0 3
            return offset;
        }
    }

    return size;
}