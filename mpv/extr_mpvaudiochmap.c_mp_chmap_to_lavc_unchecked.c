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
struct mp_chmap {int num; int* speaker; } ;

/* Variables and functions */
 scalar_t__ mp_chmap_is_unknown (struct mp_chmap*) ; 

uint64_t mp_chmap_to_lavc_unchecked(const struct mp_chmap *src)
{
    struct mp_chmap t = *src;
    if (t.num > 64)
        return 0;
    // lavc has no concept for unknown layouts yet, so pick something that does
    // the job of signaling the number of channels, even if it makes no sense
    // as a proper layout.
    if (mp_chmap_is_unknown(&t))
        return t.num == 64 ? (uint64_t)-1 : (1ULL << t.num) - 1;
    uint64_t mask = 0;
    for (int n = 0; n < t.num; n++) {
        if (t.speaker[n] < 64) // ignore MP_SPEAKER_ID_NA etc.
            mask |= 1ULL << t.speaker[n];
    }
    return mask;
}