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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_ASN1_METHOD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_pkey_asn1_meth_str (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_asn1_find_str (int /*<<< orphan*/ **,char const*,int) ; 
 int /*<<< orphan*/  EVP_PKEY_asn1_get0_info (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_paramgen_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 

int init_gen_str(EVP_PKEY_CTX **pctx,
                 const char *algname, ENGINE *e, int do_param)
{
    EVP_PKEY_CTX *ctx = NULL;
    const EVP_PKEY_ASN1_METHOD *ameth;
    ENGINE *tmpeng = NULL;
    int pkey_id;

    if (*pctx) {
        BIO_puts(bio_err, "Algorithm already set!\n");
        return 0;
    }

    ameth = EVP_PKEY_asn1_find_str(&tmpeng, algname, -1);

#ifndef OPENSSL_NO_ENGINE
    if (!ameth && e)
        ameth = ENGINE_get_pkey_asn1_meth_str(e, algname, -1);
#endif

    if (!ameth) {
        BIO_printf(bio_err, "Algorithm %s not found\n", algname);
        return 0;
    }

    ERR_clear_error();

    EVP_PKEY_asn1_get0_info(&pkey_id, NULL, NULL, NULL, NULL, ameth);
#ifndef OPENSSL_NO_ENGINE
    ENGINE_finish(tmpeng);
#endif
    ctx = EVP_PKEY_CTX_new_id(pkey_id, e);

    if (!ctx)
        goto err;
    if (do_param) {
        if (EVP_PKEY_paramgen_init(ctx) <= 0)
            goto err;
    } else {
        if (EVP_PKEY_keygen_init(ctx) <= 0)
            goto err;
    }

    *pctx = ctx;
    return 1;

 err:
    BIO_printf(bio_err, "Error initializing %s context\n", algname);
    ERR_print_errors(bio_err);
    EVP_PKEY_CTX_free(ctx);
    return 0;

}