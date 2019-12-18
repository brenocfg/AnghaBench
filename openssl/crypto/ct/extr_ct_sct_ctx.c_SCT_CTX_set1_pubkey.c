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
typedef  int /*<<< orphan*/  X509_PUBKEY ;
struct TYPE_3__ {int /*<<< orphan*/ * pkey; int /*<<< orphan*/  pkeyhashlen; int /*<<< orphan*/  pkeyhash; } ;
typedef  TYPE_1__ SCT_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_PUBKEY_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_public_key_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int SCT_CTX_set1_pubkey(SCT_CTX *sctx, X509_PUBKEY *pubkey)
{
    EVP_PKEY *pkey = X509_PUBKEY_get(pubkey);

    if (pkey == NULL)
        return 0;

    if (!ct_public_key_hash(pubkey, &sctx->pkeyhash, &sctx->pkeyhashlen)) {
        EVP_PKEY_free(pkey);
        return 0;
    }

    EVP_PKEY_free(sctx->pkey);
    sctx->pkey = pkey;
    return 1;
}