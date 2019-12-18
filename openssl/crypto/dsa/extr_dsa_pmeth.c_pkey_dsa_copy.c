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
struct TYPE_7__ {int /*<<< orphan*/  md; int /*<<< orphan*/  pmd; int /*<<< orphan*/  qbits; int /*<<< orphan*/  nbits; } ;
struct TYPE_6__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_2__ DSA_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  pkey_dsa_init (TYPE_1__*) ; 

__attribute__((used)) static int pkey_dsa_copy(EVP_PKEY_CTX *dst, const EVP_PKEY_CTX *src)
{
    DSA_PKEY_CTX *dctx, *sctx;

    if (!pkey_dsa_init(dst))
        return 0;
    sctx = src->data;
    dctx = dst->data;
    dctx->nbits = sctx->nbits;
    dctx->qbits = sctx->qbits;
    dctx->pmd = sctx->pmd;
    dctx->md = sctx->md;
    return 1;
}