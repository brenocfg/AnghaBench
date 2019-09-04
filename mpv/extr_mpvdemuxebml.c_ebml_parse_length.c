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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t ebml_parse_length(uint8_t *data, size_t data_len, int *length)
{
    *length = -1;
    uint8_t *end = data + data_len;
    if (data == end)
        return -1;
    uint64_t r = *data++;
    int len = 1;
    int len_mask;
    for (len_mask = 0x80; !(r & len_mask); len_mask >>= 1) {
        len++;
        if (len > 8)
            return -1;
    }
    r &= len_mask - 1;

    int num_allones = 0;
    if (r == len_mask - 1)
        num_allones++;
    for (int i = 1; i < len; i++) {
        if (data == end)
            return -1;
        if (*data == 255)
            num_allones++;
        r = (r << 8) | *data++;
    }
    // According to Matroska specs this means "unknown length"
    // Could be supported if there are any actual files using it
    if (num_allones == len)
        return -1;
    *length = len;
    return r;
}