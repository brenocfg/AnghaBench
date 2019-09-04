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
typedef  int npy_half ;

/* Variables and functions */

int npy_half_lt_nonan(npy_half h1, npy_half h2)
{
    if (h1&0x8000u) {
        if (h2&0x8000u) {
            return (h1&0x7fffu) > (h2&0x7fffu);
        } else {
            /* Signed zeros are equal, have to check for it */
            return (h1 != 0x8000u) || (h2 != 0x0000u);
        }
    } else {
        if (h2&0x8000u) {
            return 0;
        } else {
            return (h1&0x7fffu) < (h2&0x7fffu);
        }
    }
}