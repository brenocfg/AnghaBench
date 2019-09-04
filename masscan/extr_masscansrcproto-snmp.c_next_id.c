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
typedef  unsigned int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
next_id(const unsigned char *oid, unsigned *offset, uint64_t oid_length)
{
    uint64_t result = 0;
    while (*offset < oid_length && (oid[*offset] & 0x80)) {
        result <<= 7;
        result |= oid[(*offset)++]&0x7F;
    }
    if (*offset < oid_length) {
        result <<= 7;
        result |= oid[(*offset)++]&0x7F;
    }
    return result;
}