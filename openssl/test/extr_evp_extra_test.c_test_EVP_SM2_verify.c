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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  signature ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DigestVerifyFinal (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestVerifyUpdate (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_pkey_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_set1_id (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_SM2 ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_set_alias_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_sm3 () ; 
 int /*<<< orphan*/ * PEM_read_bio_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int test_EVP_SM2_verify(void)
{
    /* From https://tools.ietf.org/html/draft-shen-sm2-ecdsa-02#appendix-A */
    const char *pubkey =
       "-----BEGIN PUBLIC KEY-----\n"
       "MIIBMzCB7AYHKoZIzj0CATCB4AIBATAsBgcqhkjOPQEBAiEAhULWnkwETxjouSQ1\n"
       "v2/33kVyg5FcRVF9ci7biwjx38MwRAQgeHlotPoyw/0kF4Quc7v+/y88hItoMdfg\n"
       "7GUiizk35JgEIGPkxtOyOwyEnPhCQUhL/kj2HVmlsWugbm4S0donxSSaBEEEQh3r\n"
       "1hti6rZ0ZDTrw8wxXjIiCzut1QvcTE5sFH/t1D0GgFEry7QsB9RzSdIVO3DE5df9\n"
       "/L+jbqGoWEG55G4JogIhAIVC1p5MBE8Y6LkkNb9v990pdyBjBIVijVrnTufDLnm3\n"
       "AgEBA0IABArkx3mKoPEZRxvuEYJb5GICu3nipYRElel8BP9N8lSKfAJA+I8c1OFj\n"
       "Uqc8F7fxbwc1PlOhdtaEqf4Ma7eY6Fc=\n"
       "-----END PUBLIC KEY-----\n";

    const char *msg = "message digest";
    const char *id = "ALICE123@YAHOO.COM";

    const uint8_t signature[] = {
       0x30, 0x44, 0x02, 0x20,

       0x40, 0xF1, 0xEC, 0x59, 0xF7, 0x93, 0xD9, 0xF4, 0x9E, 0x09, 0xDC,
       0xEF, 0x49, 0x13, 0x0D, 0x41, 0x94, 0xF7, 0x9F, 0xB1, 0xEE, 0xD2,
       0xCA, 0xA5, 0x5B, 0xAC, 0xDB, 0x49, 0xC4, 0xE7, 0x55, 0xD1,

       0x02, 0x20,

       0x6F, 0xC6, 0xDA, 0xC3, 0x2C, 0x5D, 0x5C, 0xF1, 0x0C, 0x77, 0xDF,
       0xB2, 0x0F, 0x7C, 0x2E, 0xB6, 0x67, 0xA4, 0x57, 0x87, 0x2F, 0xB0,
       0x9E, 0xC5, 0x63, 0x27, 0xA6, 0x7E, 0xC7, 0xDE, 0xEB, 0xE7
    };

    int rc = 0;
    BIO *bio = NULL;
    EVP_PKEY *pkey = NULL;
    EVP_MD_CTX *mctx = NULL;
    EVP_PKEY_CTX *pctx = NULL;

    bio = BIO_new_mem_buf(pubkey, strlen(pubkey));
    if (!TEST_true(bio != NULL))
        goto done;

    pkey = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    if (!TEST_true(pkey != NULL))
        goto done;

    if (!TEST_true(EVP_PKEY_set_alias_type(pkey, EVP_PKEY_SM2)))
        goto done;

    if (!TEST_ptr(mctx = EVP_MD_CTX_new()))
        goto done;

    if (!TEST_ptr(pctx = EVP_PKEY_CTX_new(pkey, NULL)))
        goto done;

    if (!TEST_int_gt(EVP_PKEY_CTX_set1_id(pctx, (const uint8_t *)id,
                                          strlen(id)), 0))
        goto done;

    EVP_MD_CTX_set_pkey_ctx(mctx, pctx);

    if (!TEST_true(EVP_DigestVerifyInit(mctx, NULL, EVP_sm3(), NULL, pkey)))
        goto done;

    if (!TEST_true(EVP_DigestVerifyUpdate(mctx, msg, strlen(msg))))
        goto done;

    if (!TEST_true(EVP_DigestVerifyFinal(mctx, signature, sizeof(signature))))
        goto done;
    rc = 1;

 done:
    BIO_free(bio);
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(pctx);
    EVP_MD_CTX_free(mctx);
    return rc;
}