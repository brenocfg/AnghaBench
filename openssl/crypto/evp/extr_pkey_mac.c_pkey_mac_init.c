#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ keygen_info_count; TYPE_3__* pmeth; } ;
struct TYPE_12__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {TYPE_1__ ktmp; } ;
struct TYPE_15__ {TYPE_2__ raw_data; int /*<<< orphan*/  type; int /*<<< orphan*/ * ctx; } ;
struct TYPE_14__ {int pkey_id; } ;
typedef  TYPE_4__ MAC_PKEY_CTX ;
typedef  TYPE_5__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_PKEY_MAC_INIT ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_CMAC ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_set_data (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_TYPE_MAC ; 
 int /*<<< orphan*/  MAC_TYPE_RAW ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_4__*) ; 
 TYPE_4__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  pkey_mac_cleanup (TYPE_5__*) ; 

__attribute__((used)) static int pkey_mac_init(EVP_PKEY_CTX *ctx)
{
    MAC_PKEY_CTX *hctx;
    /* We're being smart and using the same base NIDs for PKEY and for MAC */
    int nid = ctx->pmeth->pkey_id;
    EVP_MAC *mac = EVP_MAC_fetch(NULL, OBJ_nid2sn(nid), NULL);

    if ((hctx = OPENSSL_zalloc(sizeof(*hctx))) == NULL) {
        EVPerr(EVP_F_PKEY_MAC_INIT, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    hctx->ctx = EVP_MAC_CTX_new(mac);
    if (hctx->ctx == NULL) {
        OPENSSL_free(hctx);
        return 0;
    }

    if (nid == EVP_PKEY_CMAC) {
        hctx->type = MAC_TYPE_MAC;
    } else {
        hctx->type = MAC_TYPE_RAW;
        hctx->raw_data.ktmp.type = V_ASN1_OCTET_STRING;
    }

    pkey_mac_cleanup(ctx);
    EVP_PKEY_CTX_set_data(ctx, hctx);
    ctx->keygen_info_count = 0;

    return 1;
}