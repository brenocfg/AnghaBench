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
struct TYPE_3__ {size_t strength; size_t min_entropylen; scalar_t__ min_noncelen; int /*<<< orphan*/ * get_nonce; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */

size_t rand_drbg_seedlen(RAND_DRBG *drbg)
{
    /*
     * If no os entropy source is available then RAND_seed(buffer, bufsize)
     * is expected to succeed if and only if the buffer length satisfies
     * the following requirements, which follow from the calculations
     * in RAND_DRBG_instantiate().
     */
    size_t min_entropy = drbg->strength;
    size_t min_entropylen = drbg->min_entropylen;

    /*
     * Extra entropy for the random nonce in the absence of a
     * get_nonce callback, see comment in RAND_DRBG_instantiate().
     */
    if (drbg->min_noncelen > 0 && drbg->get_nonce == NULL) {
        min_entropy += drbg->strength / 2;
        min_entropylen += drbg->min_noncelen;
    }

    /*
     * Convert entropy requirement from bits to bytes
     * (dividing by 8 without rounding upwards, because
     * all entropy requirements are divisible by 8).
     */
    min_entropy >>= 3;

    /* Return a value that satisfies both requirements */
    return min_entropy > min_entropylen ? min_entropy : min_entropylen;
}