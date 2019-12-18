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
typedef  unsigned long long uint64_t ;
struct mp_chmap {size_t num; int* speaker; } ;

/* Variables and functions */
 size_t MP_NUM_CHANNELS ; 

void mp_chmap_from_lavc(struct mp_chmap *dst, uint64_t src)
{
    dst->num = 0;
    for (int n = 0; n < 64; n++) {
        if (src & (1ULL << n)) {
            if (dst->num >= MP_NUM_CHANNELS) {
                dst->num = 0;
                return;
            }
            dst->speaker[dst->num] = n;
            dst->num++;
        }
    }
}