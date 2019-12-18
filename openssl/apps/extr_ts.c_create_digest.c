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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (char const*,long*) ; 
 unsigned char* app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int create_digest(BIO *input, const char *digest, const EVP_MD *md,
                         unsigned char **md_value)
{
    int md_value_len;
    int rv = 0;
    EVP_MD_CTX *md_ctx = NULL;

    md_value_len = EVP_MD_size(md);
    if (md_value_len < 0)
        return 0;

    if (input != NULL) {
        unsigned char buffer[4096];
        int length;

        md_ctx = EVP_MD_CTX_new();
        if (md_ctx == NULL)
            return 0;
        *md_value = app_malloc(md_value_len, "digest buffer");
        if (!EVP_DigestInit(md_ctx, md))
            goto err;
        while ((length = BIO_read(input, buffer, sizeof(buffer))) > 0) {
            if (!EVP_DigestUpdate(md_ctx, buffer, length))
                goto err;
        }
        if (!EVP_DigestFinal(md_ctx, *md_value, NULL))
            goto err;
        md_value_len = EVP_MD_size(md);
    } else {
        long digest_len;

        *md_value = OPENSSL_hexstr2buf(digest, &digest_len);
        if (*md_value == NULL || md_value_len != digest_len) {
            OPENSSL_free(*md_value);
            *md_value = NULL;
            BIO_printf(bio_err, "bad digest, %d bytes "
                       "must be specified\n", md_value_len);
            return 0;
        }
    }
    rv = md_value_len;
 err:
    EVP_MD_CTX_free(md_ctx);
    return rv;
}