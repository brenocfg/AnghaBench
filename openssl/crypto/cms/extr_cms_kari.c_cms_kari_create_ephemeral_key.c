#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pctx; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ CMS_KeyAgreeRecipientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_derive_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cms_kari_create_ephemeral_key(CMS_KeyAgreeRecipientInfo *kari,
                                         EVP_PKEY *pk)
{
    EVP_PKEY_CTX *pctx = NULL;
    EVP_PKEY *ekey = NULL;
    int rv = 0;

    pctx = EVP_PKEY_CTX_new(pk, NULL);
    if (pctx == NULL)
        goto err;
    if (EVP_PKEY_keygen_init(pctx) <= 0)
        goto err;
    if (EVP_PKEY_keygen(pctx, &ekey) <= 0)
        goto err;
    EVP_PKEY_CTX_free(pctx);
    pctx = EVP_PKEY_CTX_new(ekey, NULL);
    if (pctx == NULL)
        goto err;
    if (EVP_PKEY_derive_init(pctx) <= 0)
        goto err;
    kari->pctx = pctx;
    rv = 1;
 err:
    if (!rv)
        EVP_PKEY_CTX_free(pctx);
    EVP_PKEY_free(ekey);
    return rv;
}