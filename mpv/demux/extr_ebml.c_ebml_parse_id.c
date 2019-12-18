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
typedef  int uint32_t ;

/* Variables and functions */
 int EBML_ID_INVALID ; 

__attribute__((used)) static uint32_t ebml_parse_id(uint8_t *data, size_t data_len, int *length)
{
    *length = -1;
    uint8_t *end = data + data_len;
    if (data == end)
        return EBML_ID_INVALID;
    int len = 1;
    uint32_t id = *data++;
    for (int len_mask = 0x80; !(id & len_mask); len_mask >>= 1) {
        len++;
        if (len > 4)
            return EBML_ID_INVALID;
    }
    *length = len;
    while (--len && data < end)
        id = (id << 8) | *data++;
    return id;
}