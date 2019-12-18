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
typedef  int ULONG ;
typedef  int UINT ;
typedef  int INT ;

/* Variables and functions */
 int DSOUND_FREQSHIFT ; 

__attribute__((used)) static inline void src_advance(const void **src, UINT stride, INT *count, UINT *freqAcc, UINT adj)
{
    *freqAcc += adj;
    if (*freqAcc >= (1 << DSOUND_FREQSHIFT))
    {
        ULONG adv = (*freqAcc >> DSOUND_FREQSHIFT);
        *freqAcc &= (1 << DSOUND_FREQSHIFT) - 1;
        *(const char **)src += adv * stride;
        *count -= adv;
    }
}