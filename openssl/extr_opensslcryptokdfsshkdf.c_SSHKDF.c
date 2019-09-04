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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,...) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 

__attribute__((used)) static int SSHKDF(const EVP_MD *evp_md,
                  const unsigned char *key, size_t key_len,
                  const unsigned char *xcghash, size_t xcghash_len,
                  const unsigned char *session_id, size_t session_id_len,
                  char type, unsigned char *okey, size_t okey_len)
{
    EVP_MD_CTX *md = NULL;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int dsize = 0;
    size_t cursize = 0;
    int ret = 0;

    md = EVP_MD_CTX_new();
    if (md == NULL)
        return 0;

    if (!EVP_DigestInit_ex(md, evp_md, NULL))
        goto out;

    if (!EVP_DigestUpdate(md, key, key_len))
        goto out;

    if (!EVP_DigestUpdate(md, xcghash, xcghash_len))
        goto out;

    if (!EVP_DigestUpdate(md, &type, 1))
        goto out;

    if (!EVP_DigestUpdate(md, session_id, session_id_len))
        goto out;

    if (!EVP_DigestFinal_ex(md, digest, &dsize))
        goto out;

    if (okey_len < dsize) {
        memcpy(okey, digest, okey_len);
        ret = 1;
        goto out;
    }

    memcpy(okey, digest, dsize);

    for (cursize = dsize; cursize < okey_len; cursize += dsize) {

        if (!EVP_DigestInit_ex(md, evp_md, NULL))
            goto out;

        if (!EVP_DigestUpdate(md, key, key_len))
            goto out;

        if (!EVP_DigestUpdate(md, xcghash, xcghash_len))
            goto out;

        if (!EVP_DigestUpdate(md, okey, cursize))
            goto out;

        if (!EVP_DigestFinal_ex(md, digest, &dsize))
            goto out;

        if (okey_len < cursize + dsize) {
            memcpy(okey + cursize, digest, okey_len - cursize);
            ret = 1;
            goto out;
        }

        memcpy(okey + cursize, digest, dsize);
    }

    ret = 1;

out:
    EVP_MD_CTX_free(md);
    OPENSSL_cleanse(digest, EVP_MAX_MD_SIZE);
    return ret;
}