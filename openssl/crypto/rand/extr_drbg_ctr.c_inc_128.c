#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* V; } ;
typedef  TYPE_1__ RAND_DRBG_CTR ;

/* Variables and functions */

__attribute__((used)) static void inc_128(RAND_DRBG_CTR *ctr)
{
    int i;
    unsigned char c;
    unsigned char *p = &ctr->V[15];

    for (i = 0; i < 16; i++, p--) {
        c = *p;
        c++;
        *p = c;
        if (c != 0) {
            /* If we didn't wrap around, we're done. */
            break;
        }
    }
}