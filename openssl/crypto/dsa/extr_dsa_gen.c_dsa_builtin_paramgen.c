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
struct TYPE_3__ {int /*<<< orphan*/ * g; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; int /*<<< orphan*/  dirty_cnt; } ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GENCB_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_MONT_CTX_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int BN_check_prime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* BN_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_lshift (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_lshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mask_bits (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_value_one () ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_F_DSA_BUILTIN_PARAMGEN ; 
 int /*<<< orphan*/  DSA_R_SEED_LEN_SMALL ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_Digest (unsigned char*,int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/ * EVP_sha224 () ; 
 int /*<<< orphan*/ * EVP_sha256 () ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 int SHA224_DIGEST_LENGTH ; 
 int SHA256_DIGEST_LENGTH ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

int dsa_builtin_paramgen(DSA *ret, size_t bits, size_t qbits,
                         const EVP_MD *evpmd, const unsigned char *seed_in,
                         size_t seed_len, unsigned char *seed_out,
                         int *counter_ret, unsigned long *h_ret, BN_GENCB *cb)
{
    int ok = 0;
    unsigned char seed[SHA256_DIGEST_LENGTH];
    unsigned char md[SHA256_DIGEST_LENGTH];
    unsigned char buf[SHA256_DIGEST_LENGTH], buf2[SHA256_DIGEST_LENGTH];
    BIGNUM *r0, *W, *X, *c, *test;
    BIGNUM *g = NULL, *q = NULL, *p = NULL;
    BN_MONT_CTX *mont = NULL;
    int i, k, n = 0, m = 0, qsize = qbits >> 3;
    int counter = 0;
    int r = 0;
    BN_CTX *ctx = NULL;
    unsigned int h = 2;

    if (qsize != SHA_DIGEST_LENGTH && qsize != SHA224_DIGEST_LENGTH &&
        qsize != SHA256_DIGEST_LENGTH)
        /* invalid q size */
        return 0;

    if (evpmd == NULL) {
        if (qsize == SHA_DIGEST_LENGTH)
            evpmd = EVP_sha1();
        else if (qsize == SHA224_DIGEST_LENGTH)
            evpmd = EVP_sha224();
        else
            evpmd = EVP_sha256();
    } else {
        qsize = EVP_MD_size(evpmd);
    }

    if (bits < 512)
        bits = 512;

    bits = (bits + 63) / 64 * 64;

    if (seed_in != NULL) {
        if (seed_len < (size_t)qsize) {
            DSAerr(DSA_F_DSA_BUILTIN_PARAMGEN, DSA_R_SEED_LEN_SMALL);
            return 0;
        }
        if (seed_len > (size_t)qsize) {
            /* Only consume as much seed as is expected. */
            seed_len = qsize;
        }
        memcpy(seed, seed_in, seed_len);
    }

    if ((mont = BN_MONT_CTX_new()) == NULL)
        goto err;

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;

    BN_CTX_start(ctx);

    r0 = BN_CTX_get(ctx);
    g = BN_CTX_get(ctx);
    W = BN_CTX_get(ctx);
    q = BN_CTX_get(ctx);
    X = BN_CTX_get(ctx);
    c = BN_CTX_get(ctx);
    p = BN_CTX_get(ctx);
    test = BN_CTX_get(ctx);

    if (test == NULL)
        goto err;

    if (!BN_lshift(test, BN_value_one(), bits - 1))
        goto err;

    for (;;) {
        for (;;) {              /* find q */
            int use_random_seed = (seed_in == NULL);

            /* step 1 */
            if (!BN_GENCB_call(cb, 0, m++))
                goto err;

            if (use_random_seed) {
                if (RAND_bytes(seed, qsize) <= 0)
                    goto err;
            } else {
                /* If we come back through, use random seed next time. */
                seed_in = NULL;
            }
            memcpy(buf, seed, qsize);
            memcpy(buf2, seed, qsize);
            /* precompute "SEED + 1" for step 7: */
            for (i = qsize - 1; i >= 0; i--) {
                buf[i]++;
                if (buf[i] != 0)
                    break;
            }

            /* step 2 */
            if (!EVP_Digest(seed, qsize, md, NULL, evpmd, NULL))
                goto err;
            if (!EVP_Digest(buf, qsize, buf2, NULL, evpmd, NULL))
                goto err;
            for (i = 0; i < qsize; i++)
                md[i] ^= buf2[i];

            /* step 3 */
            md[0] |= 0x80;
            md[qsize - 1] |= 0x01;
            if (!BN_bin2bn(md, qsize, q))
                goto err;

            /* step 4 */
            r = BN_check_prime(q, ctx, cb);
            if (r > 0)
                break;
            if (r != 0)
                goto err;

            /* do a callback call */
            /* step 5 */
        }

        if (!BN_GENCB_call(cb, 2, 0))
            goto err;
        if (!BN_GENCB_call(cb, 3, 0))
            goto err;

        /* step 6 */
        counter = 0;
        /* "offset = 2" */

        n = (bits - 1) / 160;

        for (;;) {
            if ((counter != 0) && !BN_GENCB_call(cb, 0, counter))
                goto err;

            /* step 7 */
            BN_zero(W);
            /* now 'buf' contains "SEED + offset - 1" */
            for (k = 0; k <= n; k++) {
                /*
                 * obtain "SEED + offset + k" by incrementing:
                 */
                for (i = qsize - 1; i >= 0; i--) {
                    buf[i]++;
                    if (buf[i] != 0)
                        break;
                }

                if (!EVP_Digest(buf, qsize, md, NULL, evpmd, NULL))
                    goto err;

                /* step 8 */
                if (!BN_bin2bn(md, qsize, r0))
                    goto err;
                if (!BN_lshift(r0, r0, (qsize << 3) * k))
                    goto err;
                if (!BN_add(W, W, r0))
                    goto err;
            }

            /* more of step 8 */
            if (!BN_mask_bits(W, bits - 1))
                goto err;
            if (!BN_copy(X, W))
                goto err;
            if (!BN_add(X, X, test))
                goto err;

            /* step 9 */
            if (!BN_lshift1(r0, q))
                goto err;
            if (!BN_mod(c, X, r0, ctx))
                goto err;
            if (!BN_sub(r0, c, BN_value_one()))
                goto err;
            if (!BN_sub(p, X, r0))
                goto err;

            /* step 10 */
            if (BN_cmp(p, test) >= 0) {
                /* step 11 */
                r = BN_check_prime(p, ctx, cb);
                if (r > 0)
                    goto end;   /* found it */
                if (r != 0)
                    goto err;
            }

            /* step 13 */
            counter++;
            /* "offset = offset + n + 1" */

            /* step 14 */
            if (counter >= 4096)
                break;
        }
    }
 end:
    if (!BN_GENCB_call(cb, 2, 1))
        goto err;

    /* We now need to generate g */
    /* Set r0=(p-1)/q */
    if (!BN_sub(test, p, BN_value_one()))
        goto err;
    if (!BN_div(r0, NULL, test, q, ctx))
        goto err;

    if (!BN_set_word(test, h))
        goto err;
    if (!BN_MONT_CTX_set(mont, p, ctx))
        goto err;

    for (;;) {
        /* g=test^r0%p */
        if (!BN_mod_exp_mont(g, test, r0, p, ctx, mont))
            goto err;
        if (!BN_is_one(g))
            break;
        if (!BN_add(test, test, BN_value_one()))
            goto err;
        h++;
    }

    if (!BN_GENCB_call(cb, 3, 1))
        goto err;

    ok = 1;
 err:
    if (ok) {
        BN_free(ret->p);
        BN_free(ret->q);
        BN_free(ret->g);
        ret->p = BN_dup(p);
        ret->q = BN_dup(q);
        ret->g = BN_dup(g);
        ret->dirty_cnt++;
        if (ret->p == NULL || ret->q == NULL || ret->g == NULL) {
            ok = 0;
            goto err;
        }
        if (counter_ret != NULL)
            *counter_ret = counter;
        if (h_ret != NULL)
            *h_ret = h;
        if (seed_out)
            memcpy(seed_out, seed, qsize);
    }
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    BN_MONT_CTX_free(mont);
    return ok;
}