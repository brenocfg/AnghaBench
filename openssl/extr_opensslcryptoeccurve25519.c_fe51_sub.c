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
typedef  scalar_t__* fe51 ;

/* Variables and functions */

__attribute__((used)) static void fe51_sub(fe51 h, const fe51 f, const fe51 g)
{
    /*
     * Add 2*modulus to ensure that result remains positive
     * even if subtrahend is partially reduced.
     */
    h[0] = (f[0] + 0xfffffffffffda) - g[0];
    h[1] = (f[1] + 0xffffffffffffe) - g[1];
    h[2] = (f[2] + 0xffffffffffffe) - g[2];
    h[3] = (f[3] + 0xffffffffffffe) - g[3];
    h[4] = (f[4] + 0xffffffffffffe) - g[4];
}