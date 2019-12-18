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

__attribute__((used)) static inline size_t _find_emulated(uint8_t* data, size_t size)
{
    size_t offset = 2;

    while (offset < size) {
        if (3 < data[offset]) {
            // 0 0 X; we know X is not 0, 1, 2 or 3
            offset += 3;
        } else if (0 != data[offset - 1]) {
            // 0 X 0 0 1
            offset += 2;
        } else if (0 != data[offset - 2]) {
            // X 0 0 1
            offset += 1;
        } else {
            // 0 0 0, 0 0 1
            return offset;
        }
    }

    return size;
}