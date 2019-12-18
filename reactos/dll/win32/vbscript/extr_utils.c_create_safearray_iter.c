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
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int ref; TYPE_3__ IEnumVARIANT_iface; int /*<<< orphan*/  size; scalar_t__ i; TYPE_2__* sa; } ;
typedef  TYPE_1__ safearray_iter ;
struct TYPE_11__ {int fFeatures; } ;
typedef  TYPE_2__ SAFEARRAY ;
typedef  TYPE_3__ IEnumVARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int FADF_VARIANT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SafeArrayLock (TYPE_2__*) ; 
 int /*<<< orphan*/  get_safearray_size (TYPE_2__*) ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  safearray_iter_EnumVARIANTVtbl ; 

HRESULT create_safearray_iter(SAFEARRAY *sa, IEnumVARIANT **ev)
{
    safearray_iter *iter;
    HRESULT hres;

    if(sa && !(sa->fFeatures & FADF_VARIANT)) {
        FIXME("enumeration not supported: %x\n", sa->fFeatures);
        return E_NOTIMPL;
    }

    iter = heap_alloc(sizeof(*iter));
    if(!iter)
        return E_OUTOFMEMORY;

    if(sa) {
        hres = SafeArrayLock(sa);
        if(FAILED(hres)) {
            heap_free(iter);
            return hres;
        }
    }

    iter->IEnumVARIANT_iface.lpVtbl = &safearray_iter_EnumVARIANTVtbl;
    iter->ref = 1;
    iter->sa = sa;
    iter->i = 0;
    iter->size = get_safearray_size(sa);

    *ev = &iter->IEnumVARIANT_iface;
    return S_OK;
}