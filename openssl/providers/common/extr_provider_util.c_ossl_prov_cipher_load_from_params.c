#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ data_type; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * cipher; int /*<<< orphan*/ * alloc_cipher; int /*<<< orphan*/  engine; } ;
typedef  TYPE_1__ PROV_CIPHER ;
typedef  TYPE_2__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_CIPHER_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  EVP_CIPHER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_cipherbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_ALG_PARAM_CIPHER ; 
 scalar_t__ OSSL_PARAM_UTF8_STRING ; 
 TYPE_2__* OSSL_PARAM_locate_const (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_common (TYPE_2__ const*,char const**,int /*<<< orphan*/ *) ; 

int ossl_prov_cipher_load_from_params(PROV_CIPHER *pc,
                                      const OSSL_PARAM params[],
                                      OPENSSL_CTX *ctx)
{
    const OSSL_PARAM *p;
    const char *propquery;

    if (!load_common(params, &propquery, &pc->engine))
        return 0;

    p = OSSL_PARAM_locate_const(params, OSSL_ALG_PARAM_CIPHER);
    if (p == NULL)
        return 1;
    if (p->data_type != OSSL_PARAM_UTF8_STRING)
        return 0;

    EVP_CIPHER_free(pc->alloc_cipher);
    pc->cipher = pc->alloc_cipher = EVP_CIPHER_fetch(ctx, p->data, propquery);
    /* TODO legacy stuff, to be removed */
#ifndef FIPS_MODE /* Inside the FIPS module, we don't support legacy ciphers */
    if (pc->cipher == NULL)
        pc->cipher = EVP_get_cipherbyname(p->data);
#endif
    return pc->cipher != NULL;
}