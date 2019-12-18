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
typedef  int /*<<< orphan*/  PKCS7_SIGNER_INFO ;
typedef  int /*<<< orphan*/  ESS_SIGNING_CERT ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ESS_F_ESS_SIGNING_CERT_ADD ; 
 int /*<<< orphan*/  ESSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_id_smime_aa_signingCertificate ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int PKCS7_add_signed_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int i2d_ESS_SIGNING_CERT (int /*<<< orphan*/ *,unsigned char**) ; 

int ESS_SIGNING_CERT_add(PKCS7_SIGNER_INFO *si, ESS_SIGNING_CERT *sc)
{
    ASN1_STRING *seq = NULL;
    unsigned char *p, *pp = NULL;
    int len;

    len = i2d_ESS_SIGNING_CERT(sc, NULL);
    if ((pp = OPENSSL_malloc(len)) == NULL) {
        ESSerr(ESS_F_ESS_SIGNING_CERT_ADD, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    p = pp;
    i2d_ESS_SIGNING_CERT(sc, &p);
    if ((seq = ASN1_STRING_new()) == NULL || !ASN1_STRING_set(seq, pp, len)) {
        ESSerr(ESS_F_ESS_SIGNING_CERT_ADD, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    OPENSSL_free(pp);
    pp = NULL;
    return PKCS7_add_signed_attribute(si,
                                      NID_id_smime_aa_signingCertificate,
                                      V_ASN1_SEQUENCE, seq);
 err:
    ASN1_STRING_free(seq);
    OPENSSL_free(pp);

    return 0;
}