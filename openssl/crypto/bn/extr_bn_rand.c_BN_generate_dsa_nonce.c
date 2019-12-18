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
typedef  int /*<<< orphan*/  random_bytes ;
typedef  int /*<<< orphan*/  private_bytes ;
typedef  int /*<<< orphan*/  done ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_GENERATE_DSA_NONCE ; 
 int /*<<< orphan*/  BN_R_NO_SUITABLE_DIGEST ; 
 int /*<<< orphan*/  BN_R_PRIVATE_KEY_TOO_LARGE ; 
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,unsigned int const,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_bn2binpad (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int BN_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (unsigned int const) ; 
 int SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/ * bn_get_lib_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  rand_priv_bytes_ex (int /*<<< orphan*/ *,unsigned char*,int) ; 

int BN_generate_dsa_nonce(BIGNUM *out, const BIGNUM *range,
                          const BIGNUM *priv, const unsigned char *message,
                          size_t message_len, BN_CTX *ctx)
{
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    /*
     * We use 512 bits of random data per iteration to ensure that we have at
     * least |range| bits of randomness.
     */
    unsigned char random_bytes[64];
    unsigned char digest[SHA512_DIGEST_LENGTH];
    unsigned done, todo;
    /* We generate |range|+8 bytes of random output. */
    const unsigned num_k_bytes = BN_num_bytes(range) + 8;
    unsigned char private_bytes[96];
    unsigned char *k_bytes = NULL;
    int ret = 0;
    EVP_MD *md = NULL;
    OPENSSL_CTX *libctx = bn_get_lib_ctx(ctx);

    if (mdctx == NULL)
        goto err;

    k_bytes = OPENSSL_malloc(num_k_bytes);
    if (k_bytes == NULL)
        goto err;

    /* We copy |priv| into a local buffer to avoid exposing its length. */
    if (BN_bn2binpad(priv, private_bytes, sizeof(private_bytes)) < 0) {
        /*
         * No reasonable DSA or ECDSA key should have a private key this
         * large and we don't handle this case in order to avoid leaking the
         * length of the private key.
         */
        BNerr(BN_F_BN_GENERATE_DSA_NONCE, BN_R_PRIVATE_KEY_TOO_LARGE);
        goto err;
    }

    md = EVP_MD_fetch(libctx, "SHA512", NULL);
    if (md == NULL) {
        BNerr(BN_F_BN_GENERATE_DSA_NONCE, BN_R_NO_SUITABLE_DIGEST);
        goto err;
    }
    for (done = 0; done < num_k_bytes;) {
        if (!rand_priv_bytes_ex(libctx, random_bytes, sizeof(random_bytes)))
            goto err;

        if (!EVP_DigestInit_ex(mdctx, md, NULL)
                || !EVP_DigestUpdate(mdctx, &done, sizeof(done))
                || !EVP_DigestUpdate(mdctx, private_bytes,
                                     sizeof(private_bytes))
                || !EVP_DigestUpdate(mdctx, message, message_len)
                || !EVP_DigestUpdate(mdctx, random_bytes, sizeof(random_bytes))
                || !EVP_DigestFinal_ex(mdctx, digest, NULL))
            goto err;

        todo = num_k_bytes - done;
        if (todo > SHA512_DIGEST_LENGTH)
            todo = SHA512_DIGEST_LENGTH;
        memcpy(k_bytes + done, digest, todo);
        done += todo;
    }

    if (!BN_bin2bn(k_bytes, num_k_bytes, out))
        goto err;
    if (BN_mod(out, out, range, ctx) != 1)
        goto err;
    ret = 1;

 err:
    EVP_MD_CTX_free(mdctx);
    EVP_MD_free(md);
    OPENSSL_free(k_bytes);
    OPENSSL_cleanse(private_bytes, sizeof(private_bytes));
    return ret;
}