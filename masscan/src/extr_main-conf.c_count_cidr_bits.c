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
struct Range {unsigned int begin; unsigned int end; } ;

/* Variables and functions */

__attribute__((used)) static unsigned
count_cidr_bits(struct Range range)
{
    unsigned i;

    for (i=0; i<32; i++) {
        unsigned mask = 0xFFFFFFFF >> i;

        if ((range.begin & ~mask) == (range.end & ~mask)) {
            if ((range.begin & mask) == 0 && (range.end & mask) == mask)
                return i;
        }
    }

    return 0;
}