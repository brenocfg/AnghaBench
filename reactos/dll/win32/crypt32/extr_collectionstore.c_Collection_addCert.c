#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_13__ {TYPE_1__ u; } ;
typedef  TYPE_2__ context_t ;
struct TYPE_14__ {TYPE_2__ base; } ;
typedef  TYPE_3__ cert_t ;
typedef  int /*<<< orphan*/  WINE_STORE_LIST_ENTRY ;
typedef  int /*<<< orphan*/  WINE_COLLECTIONSTORE ;
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_CollectionAddContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_2__**) ; 
 scalar_t__ CRYPT_CollectionCreateContextFromChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Context_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  certs ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_vtbl_t ; 

__attribute__((used)) static BOOL Collection_addCert(WINECRYPT_CERTSTORE *store, context_t *cert,
 context_t *toReplace, context_t **ppStoreContext, BOOL use_link)
{
    BOOL ret;
    context_t *childContext = NULL;
    WINE_COLLECTIONSTORE *cs = (WINE_COLLECTIONSTORE*)store;

    ret = CRYPT_CollectionAddContext(cs, offsetof(store_vtbl_t, certs),
     cert, toReplace, &childContext);
    if (ppStoreContext && childContext)
    {
        WINE_STORE_LIST_ENTRY *storeEntry = childContext->u.ptr;
        cert_t *context = (cert_t*)CRYPT_CollectionCreateContextFromChild(cs, storeEntry,
         childContext);

        *ppStoreContext = &context->base;
    }
    if (childContext)
        Context_Release(childContext);
    return ret;
}