#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_9__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
struct TYPE_11__ {TYPE_1__* hash_algo; } ;
struct TYPE_10__ {TYPE_3__* msg_imprint; } ;
typedef  TYPE_2__ TS_TST_INFO ;
typedef  TYPE_3__ TS_MSG_IMPRINT ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (unsigned int) ; 
 int /*<<< orphan*/  TS_F_TS_COMPUTE_IMPRINT ; 
 int /*<<< orphan*/  TS_R_UNSUPPORTED_MD_ALGORITHM ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* X509_ALGOR_dup (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_ALGOR_free (TYPE_1__*) ; 

__attribute__((used)) static int ts_compute_imprint(BIO *data, TS_TST_INFO *tst_info,
                              X509_ALGOR **md_alg,
                              unsigned char **imprint, unsigned *imprint_len)
{
    TS_MSG_IMPRINT *msg_imprint = tst_info->msg_imprint;
    X509_ALGOR *md_alg_resp = msg_imprint->hash_algo;
    const EVP_MD *md;
    EVP_MD_CTX *md_ctx = NULL;
    unsigned char buffer[4096];
    int length;

    *md_alg = NULL;
    *imprint = NULL;

    if ((*md_alg = X509_ALGOR_dup(md_alg_resp)) == NULL)
        goto err;
    if ((md = EVP_get_digestbyobj((*md_alg)->algorithm)) == NULL) {
        TSerr(TS_F_TS_COMPUTE_IMPRINT, TS_R_UNSUPPORTED_MD_ALGORITHM);
        goto err;
    }
    length = EVP_MD_size(md);
    if (length < 0)
        goto err;
    *imprint_len = length;
    if ((*imprint = OPENSSL_malloc(*imprint_len)) == NULL) {
        TSerr(TS_F_TS_COMPUTE_IMPRINT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    md_ctx = EVP_MD_CTX_new();
    if (md_ctx == NULL) {
        TSerr(TS_F_TS_COMPUTE_IMPRINT, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if (!EVP_DigestInit(md_ctx, md))
        goto err;
    while ((length = BIO_read(data, buffer, sizeof(buffer))) > 0) {
        if (!EVP_DigestUpdate(md_ctx, buffer, length))
            goto err;
    }
    if (!EVP_DigestFinal(md_ctx, *imprint, NULL))
        goto err;
    EVP_MD_CTX_free(md_ctx);

    return 1;
 err:
    EVP_MD_CTX_free(md_ctx);
    X509_ALGOR_free(*md_alg);
    OPENSSL_free(*imprint);
    *imprint_len = 0;
    *imprint = 0;
    return 0;
}