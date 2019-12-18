#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * dh; scalar_t__ pad; int /*<<< orphan*/ * dhpeer; } ;
typedef  TYPE_1__ PROV_DH_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int DH_compute_key (unsigned char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int DH_compute_key_padded (unsigned char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 scalar_t__ DH_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dh_derive(void *vpdhctx, unsigned char *secret, size_t *secretlen,
                     size_t outlen)
{
    PROV_DH_CTX *pdhctx = (PROV_DH_CTX *)vpdhctx;
    int ret;
    size_t dhsize;
    const BIGNUM *pub_key = NULL;

    /* TODO(3.0): Add errors to stack */
    if (pdhctx->dh == NULL || pdhctx->dhpeer == NULL)
        return 0;

    dhsize = (size_t)DH_size(pdhctx->dh);
    if (secret == NULL) {
        *secretlen = dhsize;
        return 1;
    }
    if (outlen < dhsize)
        return 0;

    DH_get0_key(pdhctx->dhpeer, &pub_key, NULL);
    ret = (pdhctx->pad) ? DH_compute_key_padded(secret, pub_key, pdhctx->dh)
                        : DH_compute_key(secret, pub_key, pdhctx->dh);
    if (ret <= 0)
        return 0;

    *secretlen = ret;
    return 1;
}