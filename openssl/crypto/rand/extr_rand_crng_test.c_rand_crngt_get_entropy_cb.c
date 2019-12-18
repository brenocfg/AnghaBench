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
typedef  int /*<<< orphan*/  RAND_POOL ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 size_t CRNGT_BUFSIZ ; 
 int EVP_Digest (unsigned char*,size_t,unsigned char*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 size_t rand_pool_acquire_entropy (int /*<<< orphan*/ *) ; 
 unsigned char* rand_pool_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_pool_reattach (int /*<<< orphan*/ *,unsigned char*) ; 

int rand_crngt_get_entropy_cb(OPENSSL_CTX *ctx,
                              RAND_POOL *pool,
                              unsigned char *buf,
                              unsigned char *md,
                              unsigned int *md_size)
{
    int r;
    size_t n;
    unsigned char *p;

    if (pool == NULL)
        return 0;

    n = rand_pool_acquire_entropy(pool);
    if (n >= CRNGT_BUFSIZ) {
        EVP_MD *fmd = EVP_MD_fetch(ctx, "SHA256", "");
        if (fmd == NULL)
            return 0;
        p = rand_pool_detach(pool);
        r = EVP_Digest(p, CRNGT_BUFSIZ, md, md_size, fmd, NULL);
        if (r != 0)
            memcpy(buf, p, CRNGT_BUFSIZ);
        rand_pool_reattach(pool, p);
        EVP_MD_free(fmd);
        return r;
    }
    return 0;
}