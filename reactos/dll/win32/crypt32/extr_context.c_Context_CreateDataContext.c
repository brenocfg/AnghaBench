#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  context_vtbl_t ;
struct TYPE_11__ {int ref; TYPE_3__* store; int /*<<< orphan*/ * linked; int /*<<< orphan*/  const* vtbl; int /*<<< orphan*/  properties; } ;
typedef  TYPE_2__ context_t ;
struct TYPE_12__ {TYPE_1__* vtbl; } ;
typedef  TYPE_3__ WINECRYPT_CERTSTORE ;
struct TYPE_10__ {int /*<<< orphan*/  (* addref ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ContextPropertyList_Create () ; 
 TYPE_2__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

context_t *Context_CreateDataContext(size_t contextSize, const context_vtbl_t *vtbl, WINECRYPT_CERTSTORE *store)
{
    context_t *context;

    context = CryptMemAlloc(sizeof(context_t) + contextSize);
    if (!context)
        return NULL;

    context->properties = ContextPropertyList_Create();
    if (!context->properties)
    {
        CryptMemFree(context);
        return NULL;
    }

    context->vtbl = vtbl;
    context->ref = 1;
    context->linked = NULL;

    store->vtbl->addref(store);
    context->store = store;

    TRACE("returning %p\n", context);
    return context;
}