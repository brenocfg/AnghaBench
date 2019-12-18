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
typedef  int /*<<< orphan*/  dummy ;
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int RAND_DRBG_generate (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/ * RAND_DRBG_get0_master () ; 
 int /*<<< orphan*/  rand_drbg_lock (int /*<<< orphan*/ *) ; 
 int rand_drbg_restart (int /*<<< orphan*/ *,void const*,size_t,size_t) ; 
 size_t rand_drbg_seedlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_drbg_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drbg_add(const void *buf, int num, double randomness)
{
    int ret = 0;
    RAND_DRBG *drbg = RAND_DRBG_get0_master();
    size_t buflen;
    size_t seedlen;

    if (drbg == NULL)
        return 0;

    if (num < 0 || randomness < 0.0)
        return 0;

    rand_drbg_lock(drbg);
    seedlen = rand_drbg_seedlen(drbg);

    buflen = (size_t)num;

#ifdef FIPS_MODE
    /*
     * NIST SP-800-90A mandates that entropy *shall not* be provided
     * by the consuming application. By setting the randomness to zero,
     * we ensure that the buffer contents will be added to the internal
     * state of the DRBG only as additional data.
     *
     * (NIST SP-800-90Ar1, Sections 9.1 and 9.2)
     */
    randomness = 0.0;
#endif
    if (buflen < seedlen || randomness < (double) seedlen) {
#if defined(OPENSSL_RAND_SEED_NONE)
        /*
         * If no os entropy source is available, a reseeding will fail
         * inevitably. So we use a trick to mix the buffer contents into
         * the DRBG state without forcing a reseeding: we generate a
         * dummy random byte, using the buffer content as additional data.
         * Note: This won't work with RAND_DRBG_FLAG_CTR_NO_DF.
         */
        unsigned char dummy[1];

        ret = RAND_DRBG_generate(drbg, dummy, sizeof(dummy), 0, buf, buflen);
        rand_drbg_unlock(drbg);
        return ret;
#else
        /*
         * If an os entropy source is available then we declare the buffer content
         * as additional data by setting randomness to zero and trigger a regular
         * reseeding.
         */
        randomness = 0.0;
#endif
    }

    if (randomness > (double)seedlen) {
        /*
         * The purpose of this check is to bound |randomness| by a
         * relatively small value in order to prevent an integer
         * overflow when multiplying by 8 in the rand_drbg_restart()
         * call below. Note that randomness is measured in bytes,
         * not bits, so this value corresponds to eight times the
         * security strength.
         */
        randomness = (double)seedlen;
    }

    ret = rand_drbg_restart(drbg, buf, buflen, (size_t)(8 * randomness));
    rand_drbg_unlock(drbg);

    return ret;
}