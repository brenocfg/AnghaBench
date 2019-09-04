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

/* Variables and functions */
 int bn_limit_bits ; 
 int bn_limit_bits_high ; 
 int bn_limit_bits_low ; 
 int bn_limit_bits_mont ; 

int BN_get_params(int which)
{
    if (which == 0)
        return bn_limit_bits;
    else if (which == 1)
        return bn_limit_bits_high;
    else if (which == 2)
        return bn_limit_bits_low;
    else if (which == 3)
        return bn_limit_bits_mont;
    else
        return 0;
}