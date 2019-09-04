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
 int /*<<< orphan*/  npy_half_isnan (int) ; 

int npy_half_eq(npy_half h1, npy_half h2)
{
    /*
     * The equality cases are as follows:
     *   - If either value is NaN, never equal.
     *   - If the values are equal, equal.
     *   - If the values are both signed zeros, equal.
     */
    return (!npy_half_isnan(h1) && !npy_half_isnan(h2)) &&
           (h1 == h2 || ((h1 | h2) & 0x7fff) == 0);
}