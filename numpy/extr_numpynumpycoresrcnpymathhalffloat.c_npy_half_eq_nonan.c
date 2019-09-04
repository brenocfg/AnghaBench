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

int npy_half_eq_nonan(npy_half h1, npy_half h2)
{
    return (h1 == h2 || ((h1 | h2) & 0x7fff) == 0);
}