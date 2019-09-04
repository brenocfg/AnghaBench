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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {unsigned char* certder; int certderlen; unsigned char* preder; int prederlen; } ;
typedef  TYPE_1__ SCT_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  NID_ct_precert_poison ; 
 int /*<<< orphan*/  NID_ct_precert_scts ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  X509_EXTENSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_delete_ext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * X509_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_x509_cert_fixup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ct_x509_get_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int i2d_X509 (int /*<<< orphan*/ *,unsigned char**) ; 
 int i2d_re_X509_tbs (int /*<<< orphan*/ *,unsigned char**) ; 

int SCT_CTX_set1_cert(SCT_CTX *sctx, X509 *cert, X509 *presigner)
{
    unsigned char *certder = NULL, *preder = NULL;
    X509 *pretmp = NULL;
    int certderlen = 0, prederlen = 0;
    int idx = -1;
    int poison_ext_is_dup, sct_ext_is_dup;
    int poison_idx = ct_x509_get_ext(cert, NID_ct_precert_poison, &poison_ext_is_dup);

    /* Duplicate poison extensions are present - error */
    if (poison_ext_is_dup)
        goto err;

    /* If *cert doesn't have a poison extension, it isn't a precert */
    if (poison_idx == -1) {
        /* cert isn't a precert, so we shouldn't have a presigner */
        if (presigner != NULL)
            goto err;

        certderlen = i2d_X509(cert, &certder);
        if (certderlen < 0)
            goto err;
    }

    /* See if cert has a precert SCTs extension */
    idx = ct_x509_get_ext(cert, NID_ct_precert_scts, &sct_ext_is_dup);
    /* Duplicate SCT extensions are present - error */
    if (sct_ext_is_dup)
        goto err;

    if (idx >= 0 && poison_idx >= 0) {
        /*
         * cert can't both contain SCTs (i.e. have an SCT extension) and be a
         * precert (i.e. have a poison extension).
         */
        goto err;
    }

    if (idx == -1) {
        idx = poison_idx;
    }

    /*
     * If either a poison or SCT extension is present, remove it before encoding
     * cert. This, along with ct_x509_cert_fixup(), gets a TBSCertificate (see
     * RFC5280) from cert, which is what the CT log signed when it produced the
     * SCT.
     */
    if (idx >= 0) {
        X509_EXTENSION *ext;

        /* Take a copy of certificate so we don't modify passed version */
        pretmp = X509_dup(cert);
        if (pretmp == NULL)
            goto err;

        ext = X509_delete_ext(pretmp, idx);
        X509_EXTENSION_free(ext);

        if (!ct_x509_cert_fixup(pretmp, presigner))
            goto err;

        prederlen = i2d_re_X509_tbs(pretmp, &preder);
        if (prederlen <= 0)
            goto err;
    }

    X509_free(pretmp);

    OPENSSL_free(sctx->certder);
    sctx->certder = certder;
    sctx->certderlen = certderlen;

    OPENSSL_free(sctx->preder);
    sctx->preder = preder;
    sctx->prederlen = prederlen;

    return 1;
err:
    OPENSSL_free(certder);
    OPENSSL_free(preder);
    X509_free(pretmp);
    return 0;
}