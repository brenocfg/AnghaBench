#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_2__* pmeth; } ;
struct TYPE_9__ {TYPE_8__ ktmp; } ;
struct TYPE_11__ {int type; int /*<<< orphan*/  ctx; TYPE_1__ raw_data; } ;
struct TYPE_10__ {int pkey_id; } ;
typedef  TYPE_3__ MAC_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_OCTET_STRING_dup (TYPE_8__*) ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MAC_up_ref (int /*<<< orphan*/ ) ; 
 TYPE_3__* EVP_PKEY_CTX_get_data (TYPE_4__*) ; 
 int /*<<< orphan*/  EVP_PKEY_assign (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
#define  MAC_TYPE_MAC 129 
#define  MAC_TYPE_RAW 128 

__attribute__((used)) static int pkey_mac_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    MAC_PKEY_CTX *hctx = EVP_PKEY_CTX_get_data(ctx);
    int nid = ctx->pmeth->pkey_id;

    switch (hctx->type) {
    case MAC_TYPE_RAW:
        {
            ASN1_OCTET_STRING *hkey = NULL;

            if (!hctx->raw_data.ktmp.data)
                return 0;
            hkey = ASN1_OCTET_STRING_dup(&hctx->raw_data.ktmp);
            if (!hkey)
                return 0;
            EVP_PKEY_assign(pkey, nid, hkey);
        }
        break;
    case MAC_TYPE_MAC:
        {
            EVP_MAC_CTX *cmkey = EVP_MAC_CTX_dup(hctx->ctx);

            if (cmkey == NULL)
                return 0;
            if (!EVP_MAC_up_ref(EVP_MAC_CTX_mac(hctx->ctx)))
                return 0;
            EVP_PKEY_assign(pkey, nid, cmkey);
        }
        break;
    default:
        /* This should be dead code */
        return 0;
    }

    return 1;
}