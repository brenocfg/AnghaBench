#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  kdf_outlen; int /*<<< orphan*/  kdf_ukmlen; int /*<<< orphan*/ * kdf_ukm; int /*<<< orphan*/  kdf_md; int /*<<< orphan*/ * kdf_oid; int /*<<< orphan*/  kdf_type; int /*<<< orphan*/  param_nid; int /*<<< orphan*/  rfc5114_param; int /*<<< orphan*/  md; int /*<<< orphan*/  pad; int /*<<< orphan*/  use_dsa; int /*<<< orphan*/  generator; int /*<<< orphan*/  subprime_len; int /*<<< orphan*/  prime_len; } ;
struct TYPE_6__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_2__ DH_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * OBJ_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_dh_init (TYPE_1__*) ; 

__attribute__((used)) static int pkey_dh_copy(EVP_PKEY_CTX *dst, const EVP_PKEY_CTX *src)
{
    DH_PKEY_CTX *dctx, *sctx;

    if (!pkey_dh_init(dst))
        return 0;
    sctx = src->data;
    dctx = dst->data;
    dctx->prime_len = sctx->prime_len;
    dctx->subprime_len = sctx->subprime_len;
    dctx->generator = sctx->generator;
    dctx->use_dsa = sctx->use_dsa;
    dctx->pad = sctx->pad;
    dctx->md = sctx->md;
    dctx->rfc5114_param = sctx->rfc5114_param;
    dctx->param_nid = sctx->param_nid;

    dctx->kdf_type = sctx->kdf_type;
    dctx->kdf_oid = OBJ_dup(sctx->kdf_oid);
    if (dctx->kdf_oid == NULL)
        return 0;
    dctx->kdf_md = sctx->kdf_md;
    if (sctx->kdf_ukm != NULL) {
        dctx->kdf_ukm = OPENSSL_memdup(sctx->kdf_ukm, sctx->kdf_ukmlen);
        if (dctx->kdf_ukm == NULL)
          return 0;
        dctx->kdf_ukmlen = sctx->kdf_ukmlen;
    }
    dctx->kdf_outlen = sctx->kdf_outlen;
    return 1;
}