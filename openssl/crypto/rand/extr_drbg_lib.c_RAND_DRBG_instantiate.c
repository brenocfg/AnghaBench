#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t strength; size_t min_entropylen; size_t max_entropylen; size_t max_perslen; scalar_t__ state; size_t min_noncelen; size_t (* get_nonce ) (TYPE_2__*,unsigned char**,int,size_t,size_t) ;size_t max_noncelen; int reseed_next_counter; size_t (* get_entropy ) (TYPE_2__*,unsigned char**,size_t,size_t,size_t,int /*<<< orphan*/ ) ;int reseed_gen_counter; int /*<<< orphan*/  (* cleanup_nonce ) (TYPE_2__*,unsigned char*,size_t) ;int /*<<< orphan*/  (* cleanup_entropy ) (TYPE_2__*,unsigned char*,size_t) ;int /*<<< orphan*/  reseed_prop_counter; int /*<<< orphan*/  reseed_time; TYPE_1__* meth; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* instantiate ) (TYPE_2__*,unsigned char*,size_t,unsigned char*,size_t,unsigned char const*,size_t) ;} ;
typedef  TYPE_2__ RAND_DRBG ;

/* Variables and functions */
 scalar_t__ DRBG_ERROR ; 
 scalar_t__ DRBG_READY ; 
 scalar_t__ DRBG_UNINITIALISED ; 
 int /*<<< orphan*/  RAND_F_RAND_DRBG_INSTANTIATE ; 
 int /*<<< orphan*/  RAND_R_ALREADY_INSTANTIATED ; 
 int /*<<< orphan*/  RAND_R_ERROR_INSTANTIATING_DRBG ; 
 int /*<<< orphan*/  RAND_R_ERROR_RETRIEVING_ENTROPY ; 
 int /*<<< orphan*/  RAND_R_ERROR_RETRIEVING_NONCE ; 
 int /*<<< orphan*/  RAND_R_IN_ERROR_STATE ; 
 int /*<<< orphan*/  RAND_R_NO_DRBG_IMPLEMENTATION_SELECTED ; 
 int /*<<< orphan*/  RAND_R_PERSONALISATION_STRING_TOO_LONG ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub1 (TYPE_2__*,unsigned char**,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t stub2 (TYPE_2__*,unsigned char**,int,size_t,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,unsigned char*,size_t,unsigned char*,size_t,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int tsan_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsan_store (int /*<<< orphan*/ *,int) ; 

int RAND_DRBG_instantiate(RAND_DRBG *drbg,
                          const unsigned char *pers, size_t perslen)
{
    unsigned char *nonce = NULL, *entropy = NULL;
    size_t noncelen = 0, entropylen = 0;
    size_t min_entropy = drbg->strength;
    size_t min_entropylen = drbg->min_entropylen;
    size_t max_entropylen = drbg->max_entropylen;

    if (perslen > drbg->max_perslen) {
        RANDerr(RAND_F_RAND_DRBG_INSTANTIATE,
                RAND_R_PERSONALISATION_STRING_TOO_LONG);
        goto end;
    }

    if (drbg->meth == NULL) {
        RANDerr(RAND_F_RAND_DRBG_INSTANTIATE,
                RAND_R_NO_DRBG_IMPLEMENTATION_SELECTED);
        goto end;
    }

    if (drbg->state != DRBG_UNINITIALISED) {
        if (drbg->state == DRBG_ERROR)
            RANDerr(RAND_F_RAND_DRBG_INSTANTIATE, RAND_R_IN_ERROR_STATE);
        else
            RANDerr(RAND_F_RAND_DRBG_INSTANTIATE, RAND_R_ALREADY_INSTANTIATED);
        goto end;
    }

    drbg->state = DRBG_ERROR;

    /*
     * NIST SP800-90Ar1 section 9.1 says you can combine getting the entropy
     * and nonce in 1 call by increasing the entropy with 50% and increasing
     * the minimum length to accommodate the length of the nonce.
     * We do this in case a nonce is require and get_nonce is NULL.
     */
    if (drbg->min_noncelen > 0 && drbg->get_nonce == NULL) {
        min_entropy += drbg->strength / 2;
        min_entropylen += drbg->min_noncelen;
        max_entropylen += drbg->max_noncelen;
    }

    drbg->reseed_next_counter = tsan_load(&drbg->reseed_prop_counter);
    if (drbg->reseed_next_counter) {
        drbg->reseed_next_counter++;
        if(!drbg->reseed_next_counter)
            drbg->reseed_next_counter = 1;
    }

    if (drbg->get_entropy != NULL)
        entropylen = drbg->get_entropy(drbg, &entropy, min_entropy,
                                       min_entropylen, max_entropylen, 0);
    if (entropylen < min_entropylen
            || entropylen > max_entropylen) {
        RANDerr(RAND_F_RAND_DRBG_INSTANTIATE, RAND_R_ERROR_RETRIEVING_ENTROPY);
        goto end;
    }

    if (drbg->min_noncelen > 0 && drbg->get_nonce != NULL) {
        noncelen = drbg->get_nonce(drbg, &nonce, drbg->strength / 2,
                                   drbg->min_noncelen, drbg->max_noncelen);
        if (noncelen < drbg->min_noncelen || noncelen > drbg->max_noncelen) {
            RANDerr(RAND_F_RAND_DRBG_INSTANTIATE, RAND_R_ERROR_RETRIEVING_NONCE);
            goto end;
        }
    }

    if (!drbg->meth->instantiate(drbg, entropy, entropylen,
                         nonce, noncelen, pers, perslen)) {
        RANDerr(RAND_F_RAND_DRBG_INSTANTIATE, RAND_R_ERROR_INSTANTIATING_DRBG);
        goto end;
    }

    drbg->state = DRBG_READY;
    drbg->reseed_gen_counter = 1;
    drbg->reseed_time = time(NULL);
    tsan_store(&drbg->reseed_prop_counter, drbg->reseed_next_counter);

 end:
    if (entropy != NULL && drbg->cleanup_entropy != NULL)
        drbg->cleanup_entropy(drbg, entropy, entropylen);
    if (nonce != NULL && drbg->cleanup_nonce != NULL)
        drbg->cleanup_nonce(drbg, nonce, noncelen);
    if (drbg->state == DRBG_READY)
        return 1;
    return 0;
}