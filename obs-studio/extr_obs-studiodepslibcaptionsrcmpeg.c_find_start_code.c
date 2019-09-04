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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static size_t find_start_code(const uint8_t* data, size_t size)
{
    uint32_t start_code = 0xffffffff;
    for (size_t i = 1; i < size; ++i) {
        start_code = (start_code << 8) | data[i];
        if (0x00000100 == (start_code & 0xffffff00)) {
            return i - 3;
        }
    }
    return 0;
}