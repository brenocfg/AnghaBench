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
struct TYPE_3__ {scalar_t__ strength_bits; scalar_t__ alg_bits; } ;
typedef  TYPE_1__ SSL_CIPHER ;

/* Variables and functions */

int SSL_CIPHER_get_bits(const SSL_CIPHER *c, int *alg_bits)
{
    int ret = 0;

    if (c != NULL) {
        if (alg_bits != NULL)
            *alg_bits = (int)c->alg_bits;
        ret = (int)c->strength_bits;
    }
    return ret;
}