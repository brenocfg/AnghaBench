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
typedef  unsigned char EVP_PKEY_CTX ;
typedef  unsigned char EVP_PKEY ;

/* Variables and functions */
 int BN_num_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSA_get0_q (int /*<<< orphan*/ ) ; 
 int DSA_verify (int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (unsigned char*) ; 
 unsigned char* EVP_PKEY_CTX_new (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (unsigned char*) ; 
 unsigned char* EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_DSA (unsigned char*,int /*<<< orphan*/ ) ; 
 int EVP_PKEY_sign (unsigned char*,unsigned char*,size_t*,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_PKEY_sign_init (unsigned char*) ; 
 int EVP_PKEY_verify (unsigned char*,unsigned char*,size_t,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_PKEY_verify_init (unsigned char*) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_error (char*,int) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  dsakey ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sign_and_verify(int len)
{
    /*
     * Per FIPS 186-4, the hash is recommended to be the same length as q.
     * If the hash is longer than q, the leftmost N bits are used; if the hash
     * is shorter, then we left-pad (see appendix C.2.1).
     */
    size_t sigLength;
    int digestlen = BN_num_bytes(DSA_get0_q(dsakey));
    int ok = 0;

    unsigned char *dataToSign = OPENSSL_malloc(len);
    unsigned char *paddedData = OPENSSL_malloc(digestlen);
    unsigned char *signature = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    EVP_PKEY *pkey = NULL;

    if (!TEST_ptr(dataToSign) ||
        !TEST_ptr(paddedData) ||
        !TEST_int_eq(RAND_bytes(dataToSign, len), 1))
        goto end;

    memset(paddedData, 0, digestlen);
    if (len > digestlen)
        memcpy(paddedData, dataToSign, digestlen);
    else
        memcpy(paddedData + digestlen - len, dataToSign, len);

    if (!TEST_ptr(pkey = EVP_PKEY_new()))
        goto end;
    EVP_PKEY_set1_DSA(pkey, dsakey);

    if (!TEST_ptr(ctx = EVP_PKEY_CTX_new(pkey, NULL)))
        goto end;
    if (!TEST_int_eq(EVP_PKEY_sign_init(ctx), 1))
        goto end;

    if (EVP_PKEY_sign(ctx, NULL, &sigLength, dataToSign, len) != 1) {
        TEST_error("Failed to get signature length, len=%d", len);
        goto end;
    }

    if (!TEST_ptr(signature = OPENSSL_malloc(sigLength)))
        goto end;

    if (EVP_PKEY_sign(ctx, signature, &sigLength, dataToSign, len) != 1) {
        TEST_error("Failed to sign, len=%d", len);
        goto end;
    }

    /* Check that the signature is okay via the EVP interface */
    if (!TEST_int_eq(EVP_PKEY_verify_init(ctx), 1))
        goto end;

    /* ... using the same data we just signed */
    if (EVP_PKEY_verify(ctx, signature, sigLength, dataToSign, len) != 1) {
        TEST_error("EVP verify with unpadded length %d failed\n", len);
        goto end;
    }

    /* ... padding/truncating the data to the appropriate digest size */
    if (EVP_PKEY_verify(ctx, signature, sigLength, paddedData, digestlen) != 1) {
        TEST_error("EVP verify with length %d failed\n", len);
        goto end;
    }

    /* Verify again using the raw DSA interface */
    if (DSA_verify(0, dataToSign, len, signature, sigLength, dsakey) != 1) {
        TEST_error("Verification with unpadded data failed, len=%d", len);
        goto end;
    }

    if (DSA_verify(0, paddedData, digestlen, signature, sigLength, dsakey) != 1) {
        TEST_error("verify with length %d failed\n", len);
        goto end;
    }

    ok = 1;
end:
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(pkey);

    OPENSSL_free(signature);
    OPENSSL_free(paddedData);
    OPENSSL_free(dataToSign);

    return ok;
}