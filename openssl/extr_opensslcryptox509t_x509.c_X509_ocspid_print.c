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
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 unsigned char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  EVP_Digest (unsigned char*,int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/ * X509_get0_pubkey_bitstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int i2d_X509_NAME (int /*<<< orphan*/ *,unsigned char**) ; 

int X509_ocspid_print(BIO *bp, X509 *x)
{
    unsigned char *der = NULL;
    unsigned char *dertmp;
    int derlen;
    int i;
    unsigned char SHA1md[SHA_DIGEST_LENGTH];
    ASN1_BIT_STRING *keybstr;
    X509_NAME *subj;

    /*
     * display the hash of the subject as it would appear in OCSP requests
     */
    if (BIO_printf(bp, "        Subject OCSP hash: ") <= 0)
        goto err;
    subj = X509_get_subject_name(x);
    derlen = i2d_X509_NAME(subj, NULL);
    if ((der = dertmp = OPENSSL_malloc(derlen)) == NULL)
        goto err;
    i2d_X509_NAME(subj, &dertmp);

    if (!EVP_Digest(der, derlen, SHA1md, NULL, EVP_sha1(), NULL))
        goto err;
    for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
        if (BIO_printf(bp, "%02X", SHA1md[i]) <= 0)
            goto err;
    }
    OPENSSL_free(der);
    der = NULL;

    /*
     * display the hash of the public key as it would appear in OCSP requests
     */
    if (BIO_printf(bp, "\n        Public key OCSP hash: ") <= 0)
        goto err;

    keybstr = X509_get0_pubkey_bitstr(x);

    if (keybstr == NULL)
        goto err;

    if (!EVP_Digest(ASN1_STRING_get0_data(keybstr),
                    ASN1_STRING_length(keybstr), SHA1md, NULL, EVP_sha1(),
                    NULL))
        goto err;
    for (i = 0; i < SHA_DIGEST_LENGTH; i++) {
        if (BIO_printf(bp, "%02X", SHA1md[i]) <= 0)
            goto err;
    }
    BIO_printf(bp, "\n");

    return 1;
 err:
    OPENSSL_free(der);
    return 0;
}