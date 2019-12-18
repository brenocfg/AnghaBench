#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum tid_t { ____Placeholder_tid_t } tid_t ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int LibXml ; 
 int /*<<< orphan*/  S_OK ; 
 unsigned int get_libid_from_tid (int) ; 
 int /*<<< orphan*/  get_riid_from_tid (int) ; 
 int /*<<< orphan*/  get_typelib (unsigned int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** typeinfos ; 

HRESULT get_typeinfo(enum tid_t tid, ITypeInfo **typeinfo)
{
    unsigned lib = get_libid_from_tid(tid);
    ITypeLib *typelib;
    HRESULT hres;

    if (FAILED(hres = get_typelib(lib, &typelib)))
        return hres;

    if(!typeinfos[tid]) {
        ITypeInfo *ti;

        hres = ITypeLib_GetTypeInfoOfGuid(typelib, get_riid_from_tid(tid), &ti);
        if(FAILED(hres)) {
            /* try harder with typelib from msxml.dll */
            if (FAILED(hres = get_typelib(LibXml, &typelib)))
                return hres;
            hres = ITypeLib_GetTypeInfoOfGuid(typelib, get_riid_from_tid(tid), &ti);
            if(FAILED(hres)) {
                ERR("GetTypeInfoOfGuid failed: %08x\n", hres);
                return hres;
            }
        }

        if(InterlockedCompareExchangePointer((void**)(typeinfos+tid), ti, NULL))
            ITypeInfo_Release(ti);
    }

    *typeinfo = typeinfos[tid];

    ITypeInfo_AddRef(typeinfos[tid]);
    return S_OK;
}