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
struct TYPE_3__ {int /*<<< orphan*/  const* g; int /*<<< orphan*/  const* q; int /*<<< orphan*/  const* p; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/ * priv_key; } ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_bn_print (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int do_dsa_print(BIO *bp, const DSA *x, int off, int ptype)
{
    int ret = 0;
    const char *ktype = NULL;
    const BIGNUM *priv_key, *pub_key;
    int mod_len = 0;

    if (x->p != NULL)
        mod_len = BN_num_bits(x->p);

    if (ptype == 2)
        priv_key = x->priv_key;
    else
        priv_key = NULL;

    if (ptype > 0)
        pub_key = x->pub_key;
    else
        pub_key = NULL;

    if (ptype == 2)
        ktype = "Private-Key";
    else if (ptype == 1)
        ktype = "Public-Key";
    else
        ktype = "DSA-Parameters";

    if (priv_key) {
        if (!BIO_indent(bp, off, 128))
            goto err;
        if (BIO_printf(bp, "%s: (%d bit)\n", ktype, BN_num_bits(x->p))
            <= 0)
            goto err;
    } else {
        if (BIO_printf(bp, "Public-Key: (%d bit)\n", mod_len) <= 0)
            goto err;
    }

    if (!ASN1_bn_print(bp, "priv:", priv_key, NULL, off))
        goto err;
    if (!ASN1_bn_print(bp, "pub: ", pub_key, NULL, off))
        goto err;
    if (!ASN1_bn_print(bp, "P:   ", x->p, NULL, off))
        goto err;
    if (!ASN1_bn_print(bp, "Q:   ", x->q, NULL, off))
        goto err;
    if (!ASN1_bn_print(bp, "G:   ", x->g, NULL, off))
        goto err;
    ret = 1;
 err:
    return ret;
}