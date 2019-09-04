#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* secret_a; size_t* outlen; int /*<<< orphan*/ ** ecdh_ctx; } ;
typedef  TYPE_1__ loopargs_t ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 scalar_t__ COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_derive (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int /*<<< orphan*/ ** ecdh_c ; 
 size_t testnum ; 

__attribute__((used)) static int ECDH_EVP_derive_key_loop(void *args)
{
    loopargs_t *tempargs = *(loopargs_t **) args;
    EVP_PKEY_CTX *ctx = tempargs->ecdh_ctx[testnum];
    unsigned char *derived_secret = tempargs->secret_a;
    int count;
    size_t *outlen = &(tempargs->outlen[testnum]);

    for (count = 0; COND(ecdh_c[testnum][0]); count++)
        EVP_PKEY_derive(ctx, derived_secret, outlen);

    return count;
}