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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t buf_to_uint32(char *data) {
    size_t i;
    uint32_t result = 0;

    for (i = 0; i < sizeof(uint32_t); i++)
        result = (result << 8) | (unsigned char)data[i];

    return result;
}