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
typedef  int /*<<< orphan*/  ggen ;
struct TYPE_3__ {int /*<<< orphan*/  dirty_cnt; int /*<<< orphan*/ * g; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
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
 int /*<<< orphan*/  DSA_F_DSA_BUILTIN_PARAMGEN2 ; 
 int /*<<< orphan*/  DSA_R_INVALID_PARAMETERS ; 
 int /*<<< orphan*/  DSA_R_Q_NOT_PRIME ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_Digest (unsigned char*,size_t,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/ * EVP_sha224 () ; 
 int /*<<< orphan*/ * EVP_sha256 () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 scalar_t__ RAND_bytes (unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int dsa_builtin_paramgen2(DSA *ret, size_t L, size_t N,
                          const EVP_MD *evpmd, const unsigned char *seed_in,
                          size_t seed_len, int idx, unsigned char *seed_out,
                          int *counter_ret, unsigned long *h_ret,
                          BN_GENCB *cb)
{
    int ok = -1;
    unsigned char *seed = NULL, *seed_tmp = NULL;
    unsigned char md[EVP_MAX_MD_SIZE];
    int mdsize;
    BIGNUM *r0, *W, *X, *c, *test;
    BIGNUM *g = NULL, *q = NULL, *p = NULL;
    BN_MONT_CTX *mont = NULL;
    int i, k, n = 0, m = 0, qsize = N >> 3;
    int counter = 0;
    int r = 0;
    BN_CTX *ctx = NULL;
    EVP_MD_CTX *mctx = EVP_MD_CTX_new();
    unsigned int h = 2;

    if (mctx == NULL)
        goto err;

    /* make sure L > N, otherwise we'll get trapped in an infinite loop */
    if (L <= N) {
        DSAerr(DSA_F_DSA_BUILTIN_PARAMGEN2, DSA_R_INVALID_PARAMETERS);
        goto err;
    }

    if (evpmd == NULL) {
        if (N == 160)
            evpmd = EVP_sha1();
        else if (N == 224)
            evpmd = EVP_sha224();
        else
            evpmd = EVP_sha256();
    }

    mdsize = EVP_MD_size(evpmd);
    /* If unverifiable g generation only don't need seed */
    if (!ret->p || !ret->q || idx >= 0) {
        if (seed_len == 0)
            seed_len = mdsize;

        seed = OPENSSL_malloc(seed_len);

        if (seed_out)
            seed_tmp = seed_out;
        else
            seed_tmp = OPENSSL_malloc(seed_len);

        if (seed == NULL || seed_tmp == NULL)
            goto err;

        if (seed_in)
            memcpy(seed, seed_in, seed_len);

    }

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;

    if ((mont = BN_MONT_CTX_new()) == NULL)
        goto err;

    BN_CTX_start(ctx);
    r0 = BN_CTX_get(ctx);
    g = BN_CTX_get(ctx);
    W = BN_CTX_get(ctx);
    X = BN_CTX_get(ctx);
    c = BN_CTX_get(ctx);
    test = BN_CTX_get(ctx);
    if (test == NULL)
        goto err;

    /* if p, q already supplied generate g only */
    if (ret->p && ret->q) {
        p = ret->p;
        q = ret->q;
        if (idx >= 0)
            memcpy(seed_tmp, seed, seed_len);
        goto g_only;
    } else {
        p = BN_CTX_get(ctx);
        q = BN_CTX_get(ctx);
        if (q == NULL)
            goto err;
    }

    if (!BN_lshift(test, BN_value_one(), L - 1))
        goto err;
    for (;;) {
        for (;;) {              /* find q */
            unsigned char *pmd;
            /* step 1 */
            if (!BN_GENCB_call(cb, 0, m++))
                goto err;

            if (!seed_in) {
                if (RAND_bytes(seed, seed_len) <= 0)
                    goto err;
            }
            /* step 2 */
            if (!EVP_Digest(seed, seed_len, md, NULL, evpmd, NULL))
                goto err;
            /* Take least significant bits of md */
            if (mdsize > qsize)
                pmd = md + mdsize - qsize;
            else
                pmd = md;

            if (mdsize < qsize)
                memset(md + mdsize, 0, qsize - mdsize);

            /* step 3 */
            pmd[0] |= 0x80;
            pmd[qsize - 1] |= 0x01;
            if (!BN_bin2bn(pmd, qsize, q))
                goto err;

            /* step 4 */
            r = BN_check_prime(q, ctx, cb);
            if (r > 0)
                break;
            if (r != 0)
                goto err;
            /* Provided seed didn't produce a prime: error */
            if (seed_in) {
                ok = 0;
                DSAerr(DSA_F_DSA_BUILTIN_PARAMGEN2, DSA_R_Q_NOT_PRIME);
                goto err;
            }

            /* do a callback call */
            /* step 5 */
        }
        /* Copy seed to seed_out before we mess with it */
        if (seed_out)
            memcpy(seed_out, seed, seed_len);

        if (!BN_GENCB_call(cb, 2, 0))
            goto err;
        if (!BN_GENCB_call(cb, 3, 0))
            goto err;

        /* step 6 */
        counter = 0;
        /* "offset = 1" */

        n = (L - 1) / (mdsize << 3);

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
                for (i = seed_len - 1; i >= 0; i--) {
                    seed[i]++;
                    if (seed[i] != 0)
                        break;
                }

                if (!EVP_Digest(seed, seed_len, md, NULL, evpmd, NULL))
                    goto err;

                /* step 8 */
                if (!BN_bin2bn(md, mdsize, r0))
                    goto err;
                if (!BN_lshift(r0, r0, (mdsize << 3) * k))
                    goto err;
                if (!BN_add(W, W, r0))
                    goto err;
            }

            /* more of step 8 */
            if (!BN_mask_bits(W, L - 1))
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
            if (counter >= (int)(4 * L))
                break;
        }
        if (seed_in) {
            ok = 0;
            DSAerr(DSA_F_DSA_BUILTIN_PARAMGEN2, DSA_R_INVALID_PARAMETERS);
            goto err;
        }
    }
 end:
    if (!BN_GENCB_call(cb, 2, 1))
        goto err;

 g_only:

    /* We now need to generate g */
    /* Set r0=(p-1)/q */
    if (!BN_sub(test, p, BN_value_one()))
        goto err;
    if (!BN_div(r0, NULL, test, q, ctx))
        goto err;

    if (idx < 0) {
        if (!BN_set_word(test, h))
            goto err;
    } else
        h = 1;
    if (!BN_MONT_CTX_set(mont, p, ctx))
        goto err;

    for (;;) {
        static const unsigned char ggen[4] = { 0x67, 0x67, 0x65, 0x6e };
        if (idx >= 0) {
            md[0] = idx & 0xff;
            md[1] = (h >> 8) & 0xff;
            md[2] = h & 0xff;
            if (!EVP_DigestInit_ex(mctx, evpmd, NULL))
                goto err;
            if (!EVP_DigestUpdate(mctx, seed_tmp, seed_len))
                goto err;
            if (!EVP_DigestUpdate(mctx, ggen, sizeof(ggen)))
                goto err;
            if (!EVP_DigestUpdate(mctx, md, 3))
                goto err;
            if (!EVP_DigestFinal_ex(mctx, md, NULL))
                goto err;
            if (!BN_bin2bn(md, mdsize, test))
                goto err;
        }
        /* g=test^r0%p */
        if (!BN_mod_exp_mont(g, test, r0, p, ctx, mont))
            goto err;
        if (!BN_is_one(g))
            break;
        if (idx < 0 && !BN_add(test, test, BN_value_one()))
            goto err;
        h++;
        if (idx >= 0 && h > 0xffff)
            goto err;
    }

    if (!BN_GENCB_call(cb, 3, 1))
        goto err;

    ok = 1;
 err:
    if (ok == 1) {
        if (p != ret->p) {
            BN_free(ret->p);
            ret->p = BN_dup(p);
        }
        if (q != ret->q) {
            BN_free(ret->q);
            ret->q = BN_dup(q);
        }
        BN_free(ret->g);
        ret->g = BN_dup(g);
        if (ret->p == NULL || ret->q == NULL || ret->g == NULL) {
            ok = -1;
            goto err;
        }
        ret->dirty_cnt++;
        if (counter_ret != NULL)
            *counter_ret = counter;
        if (h_ret != NULL)
            *h_ret = h;
    }
    OPENSSL_free(seed);
    if (seed_out != seed_tmp)
        OPENSSL_free(seed_tmp);
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    BN_MONT_CTX_free(mont);
    EVP_MD_CTX_free(mctx);
    return ok;
}