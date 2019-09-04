#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ktmp; int /*<<< orphan*/  md; } ;
struct TYPE_5__ {int type; TYPE_1__ raw_data; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ MAC_PKEY_CTX ;
typedef  int /*<<< orphan*/  const EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/  const*) ; 
#define  MAC_TYPE_MAC 129 
#define  MAC_TYPE_RAW 128 
 int /*<<< orphan*/  pkey_mac_cleanup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pkey_mac_init (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int pkey_mac_copy(EVP_PKEY_CTX *dst, const EVP_PKEY_CTX *src)
{
    MAC_PKEY_CTX *sctx, *dctx;

    if (!pkey_mac_init(dst))
        return 0;

    sctx = EVP_PKEY_CTX_get_data(src);
    dctx = EVP_PKEY_CTX_get_data(dst);

    if (!EVP_MAC_CTX_copy(dctx->ctx, sctx->ctx))
        goto err;

    switch (dctx->type) {
    case MAC_TYPE_RAW:
        dctx->raw_data.md = sctx->raw_data.md;
        if (ASN1_STRING_get0_data(&sctx->raw_data.ktmp) != NULL &&
            !ASN1_STRING_copy(&dctx->raw_data.ktmp, &sctx->raw_data.ktmp))
            goto err;
        break;
    case MAC_TYPE_MAC:
        /* Nothing more to do */
        break;
    default:
        /* This should be dead code */
        return 0;
    }
    return 1;
 err:
    pkey_mac_cleanup (dst);
    return 0;
}