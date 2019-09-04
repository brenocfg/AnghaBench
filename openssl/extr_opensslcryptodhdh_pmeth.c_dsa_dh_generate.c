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
struct TYPE_3__ {int prime_len; int subprime_len; int use_dsa; int /*<<< orphan*/ * md; } ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  DSA ;
typedef  TYPE_1__ DH_PKEY_CTX ;
typedef  int /*<<< orphan*/  BN_GENCB ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int /*<<< orphan*/ * EVP_sha256 () ; 
 int dsa_builtin_paramgen (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dsa_builtin_paramgen2 (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DSA *dsa_dh_generate(DH_PKEY_CTX *dctx, BN_GENCB *pcb)
{
    DSA *ret;
    int rv = 0;
    int prime_len = dctx->prime_len;
    int subprime_len = dctx->subprime_len;
    const EVP_MD *md = dctx->md;
    if (dctx->use_dsa > 2)
        return NULL;
    ret = DSA_new();
    if (ret == NULL)
        return NULL;
    if (subprime_len == -1) {
        if (prime_len >= 2048)
            subprime_len = 256;
        else
            subprime_len = 160;
    }
    if (md == NULL) {
        if (prime_len >= 2048)
            md = EVP_sha256();
        else
            md = EVP_sha1();
    }
    if (dctx->use_dsa == 1)
        rv = dsa_builtin_paramgen(ret, prime_len, subprime_len, md,
                                  NULL, 0, NULL, NULL, NULL, pcb);
    else if (dctx->use_dsa == 2)
        rv = dsa_builtin_paramgen2(ret, prime_len, subprime_len, md,
                                   NULL, 0, -1, NULL, NULL, NULL, pcb);
    if (rv <= 0) {
        DSA_free(ret);
        return NULL;
    }
    return ret;
}