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
typedef  int /*<<< orphan*/  md_buf ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int EVP_CIPHER_iv_length (int /*<<< orphan*/  const*) ; 
 int EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int EVP_MAX_IV_LENGTH ; 
 int EVP_MAX_KEY_LENGTH ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 unsigned int PKCS5_SALT_LEN ; 

int EVP_BytesToKey(const EVP_CIPHER *type, const EVP_MD *md,
                   const unsigned char *salt, const unsigned char *data,
                   int datal, int count, unsigned char *key,
                   unsigned char *iv)
{
    EVP_MD_CTX *c;
    unsigned char md_buf[EVP_MAX_MD_SIZE];
    int niv, nkey, addmd = 0;
    unsigned int mds = 0, i;
    int rv = 0;
    nkey = EVP_CIPHER_key_length(type);
    niv = EVP_CIPHER_iv_length(type);
    OPENSSL_assert(nkey <= EVP_MAX_KEY_LENGTH);
    OPENSSL_assert(niv <= EVP_MAX_IV_LENGTH);

    if (data == NULL)
        return nkey;

    c = EVP_MD_CTX_new();
    if (c == NULL)
        goto err;
    for (;;) {
        if (!EVP_DigestInit_ex(c, md, NULL))
            goto err;
        if (addmd++)
            if (!EVP_DigestUpdate(c, &(md_buf[0]), mds))
                goto err;
        if (!EVP_DigestUpdate(c, data, datal))
            goto err;
        if (salt != NULL)
            if (!EVP_DigestUpdate(c, salt, PKCS5_SALT_LEN))
                goto err;
        if (!EVP_DigestFinal_ex(c, &(md_buf[0]), &mds))
            goto err;

        for (i = 1; i < (unsigned int)count; i++) {
            if (!EVP_DigestInit_ex(c, md, NULL))
                goto err;
            if (!EVP_DigestUpdate(c, &(md_buf[0]), mds))
                goto err;
            if (!EVP_DigestFinal_ex(c, &(md_buf[0]), &mds))
                goto err;
        }
        i = 0;
        if (nkey) {
            for (;;) {
                if (nkey == 0)
                    break;
                if (i == mds)
                    break;
                if (key != NULL)
                    *(key++) = md_buf[i];
                nkey--;
                i++;
            }
        }
        if (niv && (i != mds)) {
            for (;;) {
                if (niv == 0)
                    break;
                if (i == mds)
                    break;
                if (iv != NULL)
                    *(iv++) = md_buf[i];
                niv--;
                i++;
            }
        }
        if ((nkey == 0) && (niv == 0))
            break;
    }
    rv = EVP_CIPHER_key_length(type);
 err:
    EVP_MD_CTX_free(c);
    OPENSSL_cleanse(md_buf, sizeof(md_buf));
    return rv;
}