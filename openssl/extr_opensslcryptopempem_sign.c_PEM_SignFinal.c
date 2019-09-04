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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_EncodeBlock (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_SignFinal (int /*<<< orphan*/ *,unsigned char*,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PEM_F_PEM_SIGNFINAL ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PEM_SignFinal(EVP_MD_CTX *ctx, unsigned char *sigret,
                  unsigned int *siglen, EVP_PKEY *pkey)
{
    unsigned char *m;
    int i, ret = 0;
    unsigned int m_len;

    m = OPENSSL_malloc(EVP_PKEY_size(pkey));
    if (m == NULL) {
        PEMerr(PEM_F_PEM_SIGNFINAL, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_SignFinal(ctx, m, &m_len, pkey) <= 0)
        goto err;

    i = EVP_EncodeBlock(sigret, m, m_len);
    *siglen = i;
    ret = 1;
 err:
    /* ctx has been zeroed by EVP_SignFinal() */
    OPENSSL_free(m);
    return ret;
}