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
typedef  int /*<<< orphan*/  ESS_SIGNING_CERT ;
typedef  int /*<<< orphan*/  CMS_SignerInfo ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  CMS_F_CMS_ADD1_SIGNING_CERT ; 
 int /*<<< orphan*/  CMS_signed_add1_attr_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  NID_id_smime_aa_signingCertificate ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int i2d_ESS_SIGNING_CERT (int /*<<< orphan*/ *,unsigned char**) ; 

int cms_add1_signing_cert(CMS_SignerInfo *si, ESS_SIGNING_CERT *sc)
{
    ASN1_STRING *seq = NULL;
    unsigned char *p, *pp;
    int len;

    /* Add SigningCertificate signed attribute to the signer info. */
    len = i2d_ESS_SIGNING_CERT(sc, NULL);
    if ((pp = OPENSSL_malloc(len)) == NULL)
        goto err;
    p = pp;
    i2d_ESS_SIGNING_CERT(sc, &p);
    if (!(seq = ASN1_STRING_new()) || !ASN1_STRING_set(seq, pp, len))
        goto err;
    OPENSSL_free(pp);
    pp = NULL;
    if (!CMS_signed_add1_attr_by_NID(si, NID_id_smime_aa_signingCertificate,
                                     V_ASN1_SEQUENCE, seq, -1))
        goto err;
    ASN1_STRING_free(seq);
    return 1;
 err:
    CMSerr(CMS_F_CMS_ADD1_SIGNING_CERT, ERR_R_MALLOC_FAILURE);
    ASN1_STRING_free(seq);
    OPENSSL_free(pp);
    return 0;
}