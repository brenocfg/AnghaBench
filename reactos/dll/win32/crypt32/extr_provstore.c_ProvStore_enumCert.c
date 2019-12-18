#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  context_t ;
struct TYPE_9__ {int /*<<< orphan*/ * hCertStore; } ;
struct TYPE_10__ {int /*<<< orphan*/  base; TYPE_3__ ctx; } ;
typedef  TYPE_4__ cert_t ;
struct TYPE_11__ {TYPE_6__* memStore; } ;
typedef  TYPE_5__ WINE_PROVIDERSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
struct TYPE_12__ {TYPE_2__* vtbl; } ;
struct TYPE_7__ {scalar_t__ (* enumContext ) (TYPE_6__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_1__ certs; } ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static context_t *ProvStore_enumCert(WINECRYPT_CERTSTORE *store, context_t *prev)
{
    WINE_PROVIDERSTORE *ps = (WINE_PROVIDERSTORE*)store;
    cert_t *ret;

    ret = (cert_t*)ps->memStore->vtbl->certs.enumContext(ps->memStore, prev);
    if (!ret)
        return NULL;

    /* same dirty trick: replace the returned context's hCertStore with
     * store.
     */
    ret->ctx.hCertStore = store;
    return &ret->base;
}