#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_8__ {int /*<<< orphan*/  memid; } ;
struct TYPE_7__ {unsigned int cFuncs; } ;
typedef  TYPE_1__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FUNCDESC ;
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_GetFuncDesc (int /*<<< orphan*/ *,unsigned int,TYPE_2__**) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseFuncDesc (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  get_typeinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * heap_alloc (unsigned int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  id_cmp ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 

HRESULT get_dispids(tid_t tid, DWORD *ret_size, DISPID **ret)
{
    unsigned i, func_cnt;
    FUNCDESC *funcdesc;
    ITypeInfo *ti;
    TYPEATTR *attr;
    DISPID *ids;
    HRESULT hres;

    hres = get_typeinfo(tid, &ti);
    if(FAILED(hres))
        return hres;

    hres = ITypeInfo_GetTypeAttr(ti, &attr);
    if(FAILED(hres)) {
        ITypeInfo_Release(ti);
        return hres;
    }

    func_cnt = attr->cFuncs;
    ITypeInfo_ReleaseTypeAttr(ti, attr);

    ids = heap_alloc(func_cnt*sizeof(DISPID));
    if(!ids) {
        ITypeInfo_Release(ti);
        return E_OUTOFMEMORY;
    }

    for(i=0; i < func_cnt; i++) {
        hres = ITypeInfo_GetFuncDesc(ti, i, &funcdesc);
        if(FAILED(hres))
            break;

        ids[i] = funcdesc->memid;
        ITypeInfo_ReleaseFuncDesc(ti, funcdesc);
    }

    ITypeInfo_Release(ti);
    if(FAILED(hres)) {
        heap_free(ids);
        return hres;
    }

    qsort(ids, func_cnt, sizeof(DISPID), id_cmp);

    *ret_size = func_cnt;
    *ret = ids;
    return S_OK;
}