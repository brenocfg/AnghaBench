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
struct TYPE_6__ {int /*<<< orphan*/  kdf_oid; struct TYPE_6__* kdf_ukm; } ;
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_2__ DH_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 

__attribute__((used)) static void pkey_dh_cleanup(EVP_PKEY_CTX *ctx)
{
    DH_PKEY_CTX *dctx = ctx->data;
    if (dctx != NULL) {
        OPENSSL_free(dctx->kdf_ukm);
        ASN1_OBJECT_free(dctx->kdf_oid);
        OPENSSL_free(dctx);
    }
}