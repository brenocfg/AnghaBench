#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/  crngt_prev; int /*<<< orphan*/  crngt_pool; } ;
struct TYPE_5__ {int /*<<< orphan*/  libctx; } ;
typedef  int /*<<< orphan*/  RAND_POOL ;
typedef  TYPE_1__ RAND_DRBG ;
typedef  TYPE_2__ CRNG_TEST_GLOBAL ;

/* Variables and functions */
 int CRNGT_BUFSIZ ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  OPENSSL_CTX_RAND_CRNGT_INDEX ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  crngt_get_entropy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned char*,unsigned int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 TYPE_2__* openssl_ctx_get_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_crng_ossl_ctx_method ; 
 int /*<<< orphan*/  rand_pool_add (int /*<<< orphan*/ *,unsigned char*,size_t,size_t) ; 
 size_t rand_pool_bytes_needed (int /*<<< orphan*/ *,int) ; 
 unsigned char* rand_pool_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rand_pool_new (int,int,size_t,size_t) ; 

size_t rand_crngt_get_entropy(RAND_DRBG *drbg,
                              unsigned char **pout,
                              int entropy, size_t min_len, size_t max_len,
                              int prediction_resistance)
{
    unsigned char buf[CRNGT_BUFSIZ], md[EVP_MAX_MD_SIZE];
    unsigned int sz;
    RAND_POOL *pool;
    size_t q, r = 0, s, t = 0;
    int attempts = 3;
    CRNG_TEST_GLOBAL *crngt_glob
        = openssl_ctx_get_data(drbg->libctx, OPENSSL_CTX_RAND_CRNGT_INDEX,
                               &rand_crng_ossl_ctx_method);

    if (crngt_glob == NULL)
        return 0;

    if ((pool = rand_pool_new(entropy, 1, min_len, max_len)) == NULL)
        return 0;

    while ((q = rand_pool_bytes_needed(pool, 1)) > 0 && attempts-- > 0) {
        s = q > sizeof(buf) ? sizeof(buf) : q;
        if (!crngt_get_entropy(drbg->libctx, crngt_glob->crngt_pool, buf, md,
                               &sz)
            || memcmp(crngt_glob->crngt_prev, md, sz) == 0
            || !rand_pool_add(pool, buf, s, s * 8))
            goto err;
        memcpy(crngt_glob->crngt_prev, md, sz);
        t += s;
        attempts++;
    }
    r = t;
    *pout = rand_pool_detach(pool);
err:
    OPENSSL_cleanse(buf, sizeof(buf));
    rand_pool_free(pool);
    return r;
}