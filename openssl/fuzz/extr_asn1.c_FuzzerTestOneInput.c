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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_ITEM_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_item_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_item_free (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_item_i2d (int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_item_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_null () ; 
 int /*<<< orphan*/  DH ; 
 int /*<<< orphan*/  DHparams_print ; 
 int /*<<< orphan*/  DO_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TEST_NO_PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TEST_PRINT_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TEST_PRINT_PCTX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSA ; 
 int /*<<< orphan*/  DSA_SIG ; 
 int /*<<< orphan*/  DSA_print ; 
 int /*<<< orphan*/  DSAparams_print ; 
 int /*<<< orphan*/  ECDSA_SIG ; 
 int /*<<< orphan*/  ECPKParameters_print ; 
 int /*<<< orphan*/  ECParameters_print ; 
 int /*<<< orphan*/  EC_GROUP ; 
 int /*<<< orphan*/  EC_KEY ; 
 int /*<<< orphan*/  EC_KEY_print ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ESS_CERT_ID ; 
 int /*<<< orphan*/  ESS_CERT_ID_V2 ; 
 int /*<<< orphan*/  ESS_ISSUER_SERIAL ; 
 int /*<<< orphan*/  ESS_SIGNING_CERT ; 
 int /*<<< orphan*/  ESS_SIGNING_CERT_V2 ; 
 int /*<<< orphan*/  EVP_PKEY ; 
 int /*<<< orphan*/  EVP_PKEY_print_private ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  RSA ; 
 int /*<<< orphan*/  RSA_print ; 
 int /*<<< orphan*/  SSL_SESSION ; 
 int /*<<< orphan*/  SSL_SESSION_print ; 
 int /*<<< orphan*/  TS_ACCURACY ; 
 int /*<<< orphan*/  TS_MSG_IMPRINT ; 
 int /*<<< orphan*/  TS_MSG_IMPRINT_print_bio ; 
 int /*<<< orphan*/  TS_REQ ; 
 int /*<<< orphan*/  TS_REQ_print_bio ; 
 int /*<<< orphan*/  TS_RESP ; 
 int /*<<< orphan*/  TS_RESP_print_bio ; 
 int /*<<< orphan*/  TS_STATUS_INFO ; 
 int /*<<< orphan*/  TS_STATUS_INFO_print_bio ; 
 int /*<<< orphan*/  TS_TST_INFO ; 
 int /*<<< orphan*/  TS_TST_INFO_print_bio ; 
 int /*<<< orphan*/  d2i_AutoPrivateKey ; 
 int /*<<< orphan*/  d2i_DHparams ; 
 int /*<<< orphan*/  d2i_DHxparams ; 
 int /*<<< orphan*/  d2i_DSAPrivateKey ; 
 int /*<<< orphan*/  d2i_DSAPublicKey ; 
 int /*<<< orphan*/  d2i_DSA_SIG ; 
 int /*<<< orphan*/  d2i_DSAparams ; 
 int /*<<< orphan*/  d2i_ECDSA_SIG ; 
 int /*<<< orphan*/  d2i_ECPKParameters ; 
 int /*<<< orphan*/  d2i_ECParameters ; 
 int /*<<< orphan*/  d2i_ECPrivateKey ; 
 int /*<<< orphan*/  d2i_ESS_CERT_ID ; 
 int /*<<< orphan*/  d2i_ESS_CERT_ID_V2 ; 
 int /*<<< orphan*/  d2i_ESS_ISSUER_SERIAL ; 
 int /*<<< orphan*/  d2i_ESS_SIGNING_CERT ; 
 int /*<<< orphan*/  d2i_ESS_SIGNING_CERT_V2 ; 
 int /*<<< orphan*/  d2i_RSAPublicKey ; 
 int /*<<< orphan*/  d2i_SSL_SESSION ; 
 int /*<<< orphan*/  d2i_TS_ACCURACY ; 
 int /*<<< orphan*/  d2i_TS_MSG_IMPRINT ; 
 int /*<<< orphan*/  d2i_TS_REQ ; 
 int /*<<< orphan*/  d2i_TS_RESP ; 
 int /*<<< orphan*/  d2i_TS_STATUS_INFO ; 
 int /*<<< orphan*/  d2i_TS_TST_INFO ; 
 int /*<<< orphan*/  i2d_DHparams ; 
 int /*<<< orphan*/  i2d_DHxparams ; 
 int /*<<< orphan*/  i2d_DSAPrivateKey ; 
 int /*<<< orphan*/  i2d_DSAPublicKey ; 
 int /*<<< orphan*/  i2d_DSA_SIG ; 
 int /*<<< orphan*/  i2d_DSAparams ; 
 int /*<<< orphan*/  i2d_ECDSA_SIG ; 
 int /*<<< orphan*/  i2d_ECPKParameters ; 
 int /*<<< orphan*/  i2d_ECParameters ; 
 int /*<<< orphan*/  i2d_ECPrivateKey ; 
 int /*<<< orphan*/  i2d_ESS_CERT_ID ; 
 int /*<<< orphan*/  i2d_ESS_CERT_ID_V2 ; 
 int /*<<< orphan*/  i2d_ESS_ISSUER_SERIAL ; 
 int /*<<< orphan*/  i2d_ESS_SIGNING_CERT ; 
 int /*<<< orphan*/  i2d_ESS_SIGNING_CERT_V2 ; 
 int /*<<< orphan*/  i2d_PrivateKey ; 
 int /*<<< orphan*/  i2d_RSAPublicKey ; 
 int /*<<< orphan*/  i2d_SSL_SESSION ; 
 int /*<<< orphan*/  i2d_TS_ACCURACY ; 
 int /*<<< orphan*/  i2d_TS_MSG_IMPRINT ; 
 int /*<<< orphan*/  i2d_TS_REQ ; 
 int /*<<< orphan*/  i2d_TS_RESP ; 
 int /*<<< orphan*/  i2d_TS_STATUS_INFO ; 
 int /*<<< orphan*/  i2d_TS_TST_INFO ; 
 int /*<<< orphan*/ ** item_type ; 
 int /*<<< orphan*/  pctx ; 

int FuzzerTestOneInput(const uint8_t *buf, size_t len)
{
    int n;


    for (n = 0; item_type[n] != NULL; ++n) {
        const uint8_t *b = buf;
        unsigned char *der = NULL;
        const ASN1_ITEM *i = ASN1_ITEM_ptr(item_type[n]);
        ASN1_VALUE *o = ASN1_item_d2i(NULL, &b, len, i);

        if (o != NULL) {
            BIO *bio = BIO_new(BIO_s_null());

            ASN1_item_print(bio, o, 4, i, pctx);
            BIO_free(bio);
            ASN1_item_i2d(o, &der, i);
            OPENSSL_free(der);
            ASN1_item_free(o, i);
        }
    }

#ifndef OPENSSL_NO_TS
    DO_TEST(TS_REQ, d2i_TS_REQ, i2d_TS_REQ, TS_REQ_print_bio);
    DO_TEST(TS_MSG_IMPRINT, d2i_TS_MSG_IMPRINT, i2d_TS_MSG_IMPRINT, TS_MSG_IMPRINT_print_bio);
    DO_TEST(TS_RESP, d2i_TS_RESP, i2d_TS_RESP, TS_RESP_print_bio);
    DO_TEST(TS_STATUS_INFO, d2i_TS_STATUS_INFO, i2d_TS_STATUS_INFO, TS_STATUS_INFO_print_bio);
    DO_TEST(TS_TST_INFO, d2i_TS_TST_INFO, i2d_TS_TST_INFO, TS_TST_INFO_print_bio);
    DO_TEST_NO_PRINT(TS_ACCURACY, d2i_TS_ACCURACY, i2d_TS_ACCURACY);
#endif
    DO_TEST_NO_PRINT(ESS_ISSUER_SERIAL, d2i_ESS_ISSUER_SERIAL, i2d_ESS_ISSUER_SERIAL);
    DO_TEST_NO_PRINT(ESS_CERT_ID, d2i_ESS_CERT_ID, i2d_ESS_CERT_ID);
    DO_TEST_NO_PRINT(ESS_SIGNING_CERT, d2i_ESS_SIGNING_CERT, i2d_ESS_SIGNING_CERT);
    DO_TEST_NO_PRINT(ESS_CERT_ID_V2, d2i_ESS_CERT_ID_V2, i2d_ESS_CERT_ID_V2);
    DO_TEST_NO_PRINT(ESS_SIGNING_CERT_V2, d2i_ESS_SIGNING_CERT_V2, i2d_ESS_SIGNING_CERT_V2);
#ifndef OPENSSL_NO_DH
    DO_TEST(DH, d2i_DHparams, i2d_DHparams, DHparams_print);
    DO_TEST(DH, d2i_DHxparams, i2d_DHxparams, DHparams_print);
#endif
#ifndef OPENSSL_NO_DSA
    DO_TEST_NO_PRINT(DSA_SIG, d2i_DSA_SIG, i2d_DSA_SIG);
    DO_TEST_PRINT_OFFSET(DSA, d2i_DSAPrivateKey, i2d_DSAPrivateKey, DSA_print);
    DO_TEST_PRINT_OFFSET(DSA, d2i_DSAPublicKey, i2d_DSAPublicKey, DSA_print);
    DO_TEST(DSA, d2i_DSAparams, i2d_DSAparams, DSAparams_print);
#endif
    DO_TEST_PRINT_OFFSET(RSA, d2i_RSAPublicKey, i2d_RSAPublicKey, RSA_print);
#ifndef OPENSSL_NO_EC
    DO_TEST_PRINT_OFFSET(EC_GROUP, d2i_ECPKParameters, i2d_ECPKParameters, ECPKParameters_print);
    DO_TEST_PRINT_OFFSET(EC_KEY, d2i_ECPrivateKey, i2d_ECPrivateKey, EC_KEY_print);
    DO_TEST(EC_KEY, d2i_ECParameters, i2d_ECParameters, ECParameters_print);
    DO_TEST_NO_PRINT(ECDSA_SIG, d2i_ECDSA_SIG, i2d_ECDSA_SIG);
#endif
    DO_TEST_PRINT_PCTX(EVP_PKEY, d2i_AutoPrivateKey, i2d_PrivateKey, EVP_PKEY_print_private);
    DO_TEST(SSL_SESSION, d2i_SSL_SESSION, i2d_SSL_SESSION, SSL_SESSION_print);

    ERR_clear_error();

    return 0;
}