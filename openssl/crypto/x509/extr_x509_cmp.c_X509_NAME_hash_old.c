#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* bytes; } ;
typedef  TYPE_2__ X509_NAME ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_DIGEST_NAME_MD5 ; 
 int /*<<< orphan*/  i2d_X509_NAME (TYPE_2__*,int /*<<< orphan*/ *) ; 

unsigned long X509_NAME_hash_old(X509_NAME *x)
{
    EVP_MD *md5 = EVP_MD_fetch(NULL, OSSL_DIGEST_NAME_MD5, "-fips");
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    unsigned long ret = 0;
    unsigned char md[16];

    if (md5 == NULL || md_ctx == NULL)
        goto end;

    /* Make sure X509_NAME structure contains valid cached encoding */
    i2d_X509_NAME(x, NULL);
    if (EVP_DigestInit_ex(md_ctx, md5, NULL)
        && EVP_DigestUpdate(md_ctx, x->bytes->data, x->bytes->length)
        && EVP_DigestFinal_ex(md_ctx, md, NULL))
        ret = (((unsigned long)md[0]) | ((unsigned long)md[1] << 8L) |
               ((unsigned long)md[2] << 16L) | ((unsigned long)md[3] << 24L)
            ) & 0xffffffffL;

 end:
    EVP_MD_CTX_free(md_ctx);
    EVP_MD_free(md5);

    return ret;
}