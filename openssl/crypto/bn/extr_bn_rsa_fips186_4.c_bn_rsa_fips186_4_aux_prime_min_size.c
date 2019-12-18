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

__attribute__((used)) static int bn_rsa_fips186_4_aux_prime_min_size(int nbits)
{
    if (nbits >= 3072)
        return 171;
    if (nbits == 2048)
        return 141;
    return 0;
}