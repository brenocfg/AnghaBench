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
struct TYPE_3__ {int seedlen; scalar_t__ length; int /*<<< orphan*/ * counter; int /*<<< orphan*/ * seed; int /*<<< orphan*/ * j; int /*<<< orphan*/ * q; int /*<<< orphan*/ * g; int /*<<< orphan*/ * p; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/ * priv_key; } ;
typedef  TYPE_1__ DH ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_bn_print (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_F_DO_DH_PRINT ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int) ; 
 int ERR_R_BUF_LIB ; 
 int ERR_R_PASSED_NULL_PARAMETER ; 

__attribute__((used)) static int do_dh_print(BIO *bp, const DH *x, int indent, int ptype)
{
    int reason = ERR_R_BUF_LIB;
    const char *ktype = NULL;
    BIGNUM *priv_key, *pub_key;

    if (ptype == 2)
        priv_key = x->priv_key;
    else
        priv_key = NULL;

    if (ptype > 0)
        pub_key = x->pub_key;
    else
        pub_key = NULL;

    if (x->p == NULL || (ptype == 2 && priv_key == NULL)
            || (ptype > 0 && pub_key == NULL)) {
        reason = ERR_R_PASSED_NULL_PARAMETER;
        goto err;
    }

    if (ptype == 2)
        ktype = "DH Private-Key";
    else if (ptype == 1)
        ktype = "DH Public-Key";
    else
        ktype = "DH Parameters";

    BIO_indent(bp, indent, 128);
    if (BIO_printf(bp, "%s: (%d bit)\n", ktype, BN_num_bits(x->p)) <= 0)
        goto err;
    indent += 4;

    if (!ASN1_bn_print(bp, "private-key:", priv_key, NULL, indent))
        goto err;
    if (!ASN1_bn_print(bp, "public-key:", pub_key, NULL, indent))
        goto err;

    if (!ASN1_bn_print(bp, "prime:", x->p, NULL, indent))
        goto err;
    if (!ASN1_bn_print(bp, "generator:", x->g, NULL, indent))
        goto err;
    if (x->q && !ASN1_bn_print(bp, "subgroup order:", x->q, NULL, indent))
        goto err;
    if (x->j && !ASN1_bn_print(bp, "subgroup factor:", x->j, NULL, indent))
        goto err;
    if (x->seed) {
        int i;
        BIO_indent(bp, indent, 128);
        BIO_puts(bp, "seed:");
        for (i = 0; i < x->seedlen; i++) {
            if ((i % 15) == 0) {
                if (BIO_puts(bp, "\n") <= 0
                    || !BIO_indent(bp, indent + 4, 128))
                    goto err;
            }
            if (BIO_printf(bp, "%02x%s", x->seed[i],
                           ((i + 1) == x->seedlen) ? "" : ":") <= 0)
                goto err;
        }
        if (BIO_write(bp, "\n", 1) <= 0)
            return 0;
    }
    if (x->counter && !ASN1_bn_print(bp, "counter:", x->counter, NULL, indent))
        goto err;
    if (x->length != 0) {
        BIO_indent(bp, indent, 128);
        if (BIO_printf(bp, "recommended-private-length: %d bits\n",
                       (int)x->length) <= 0)
            goto err;
    }

    return 1;

 err:
    DHerr(DH_F_DO_DH_PRINT, reason);
    return 0;
}