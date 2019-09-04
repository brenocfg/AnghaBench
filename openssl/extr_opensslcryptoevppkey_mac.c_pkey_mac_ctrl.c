#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* data; int length; } ;
struct TYPE_14__ {int /*<<< orphan*/  engine; TYPE_2__* pkey; } ;
struct TYPE_12__ {void* md; int /*<<< orphan*/  ktmp; } ;
struct TYPE_13__ {int /*<<< orphan*/  ctx; TYPE_3__ raw_data; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {scalar_t__ ptr; } ;
struct TYPE_11__ {TYPE_1__ pkey; } ;
typedef  TYPE_4__ MAC_PKEY_CTX ;
typedef  TYPE_5__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  TYPE_6__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_CIPHER ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_ENGINE ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_KEY ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_MD ; 
 int /*<<< orphan*/  EVP_MAC_CTRL_SET_SIZE ; 
 int /*<<< orphan*/  EVP_MAC_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVP_MAC_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,...) ; 
 int EVP_MAC_init (int /*<<< orphan*/ ) ; 
#define  EVP_PKEY_CTRL_CIPHER 134 
#define  EVP_PKEY_CTRL_DIGESTINIT 133 
#define  EVP_PKEY_CTRL_MD 132 
#define  EVP_PKEY_CTRL_SET_DIGEST_SIZE 131 
#define  EVP_PKEY_CTRL_SET_MAC_KEY 130 
 TYPE_4__* EVP_PKEY_CTX_get_data (TYPE_5__*) ; 
#define  MAC_TYPE_MAC 129 
#define  MAC_TYPE_RAW 128 

__attribute__((used)) static int pkey_mac_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    MAC_PKEY_CTX *hctx = EVP_PKEY_CTX_get_data(ctx);

    switch (type) {

    case EVP_PKEY_CTRL_CIPHER:
        switch (hctx->type) {
        case MAC_TYPE_RAW:
            return -2;       /* The raw types don't support ciphers */
        case MAC_TYPE_MAC:
            {
                int rv;

                if ((rv = EVP_MAC_ctrl(hctx->ctx, EVP_MAC_CTRL_SET_ENGINE,
                                       ctx->engine)) <= 0
                    || (rv = EVP_MAC_ctrl(hctx->ctx, EVP_MAC_CTRL_SET_CIPHER,
                                          p2)) <= 0
                    || !(rv = EVP_MAC_init(hctx->ctx)))
                    return rv;
            }
            break;
        default:
            /* This should be dead code */
            return 0;
        }
        break;

    case EVP_PKEY_CTRL_MD:
        switch (hctx->type) {
        case MAC_TYPE_RAW:
            hctx->raw_data.md = p2;
            break;
        case MAC_TYPE_MAC:
            if (ctx->pkey != NULL
                && !EVP_MAC_CTX_copy(hctx->ctx,
                                     (EVP_MAC_CTX *)ctx->pkey->pkey.ptr))
                return 0;
            if (!EVP_MAC_init(hctx->ctx))
                return 0;
            break;
        default:
            /* This should be dead code */
            return 0;
        }
        break;

    case EVP_PKEY_CTRL_SET_DIGEST_SIZE:
        return EVP_MAC_ctrl(hctx->ctx, EVP_MAC_CTRL_SET_SIZE, (size_t)p1);

    case EVP_PKEY_CTRL_SET_MAC_KEY:
        switch (hctx->type) {
        case MAC_TYPE_RAW:
            if ((!p2 && p1 > 0) || (p1 < -1))
                return 0;
            if (!ASN1_OCTET_STRING_set(&hctx->raw_data.ktmp, p2, p1))
                return 0;
            break;
        case MAC_TYPE_MAC:
            if (EVP_MAC_ctrl(hctx->ctx, EVP_MAC_CTRL_SET_KEY, p2, p1) <= 0)
                return 0;
            break;
        default:
            /* This should be dead code */
            return 0;
        }
        break;

    case EVP_PKEY_CTRL_DIGESTINIT:
        switch (hctx->type) {
        case MAC_TYPE_RAW:
            /* Ensure that we have attached the implementation */
            if (!EVP_MAC_init(hctx->ctx))
                return 0;
            {
                int rv;
                ASN1_OCTET_STRING *key =
                    (ASN1_OCTET_STRING *)ctx->pkey->pkey.ptr;

                if ((rv = EVP_MAC_ctrl(hctx->ctx, EVP_MAC_CTRL_SET_ENGINE,
                                       ctx->engine)) <= 0
                    || (rv = EVP_MAC_ctrl(hctx->ctx, EVP_MAC_CTRL_SET_MD,
                                          hctx->raw_data.md)) <= 0
                    || (rv = EVP_MAC_ctrl(hctx->ctx, EVP_MAC_CTRL_SET_KEY,
                                          key->data, key->length)) <= 0)
                    return rv;
            }
            break;
        case MAC_TYPE_MAC:
            return -2;       /* The mac types don't support ciphers */
        default:
            /* This should be dead code */
            return 0;
        }
        break;

    default:
        return -2;

    }
    return 1;
}