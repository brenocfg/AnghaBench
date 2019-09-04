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
 size_t CRNGT_BUFSIZ ; 
 int EVP_Digest (unsigned char*,size_t,unsigned char*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  crngt_pool ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 size_t rand_pool_acquire_entropy (int /*<<< orphan*/ ) ; 
 unsigned char* rand_pool_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_pool_reattach (int /*<<< orphan*/ ,unsigned char*) ; 

int rand_crngt_get_entropy_cb(unsigned char *buf, unsigned char *md,
                              unsigned int *md_size)
{
    int r;
    size_t n;
    unsigned char *p;

    n = rand_pool_acquire_entropy(crngt_pool);
    if (n >= CRNGT_BUFSIZ) {
        p = rand_pool_detach(crngt_pool);
        r = EVP_Digest(p, CRNGT_BUFSIZ, md, md_size, EVP_sha256(), NULL);
        if (r != 0)
            memcpy(buf, p, CRNGT_BUFSIZ);
        rand_pool_reattach(crngt_pool, p);
        return r;
    }
    return 0;
}