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
typedef  scalar_t__ WORD ;
struct TYPE_8__ {scalar_t__ syskind; } ;
struct TYPE_7__ {scalar_t__ typekind; int cbSizeVft; int /*<<< orphan*/  guid; scalar_t__ cFuncs; } ;
typedef  scalar_t__ TYPEKIND ;
typedef  TYPE_1__ TYPEATTR ;
typedef  TYPE_2__ TLIBATTR ;
typedef  scalar_t__ SYSKIND ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HREFTYPE ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_GetContainingTypeLib (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeOfImplType (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ITypeLib_GetLibAttr (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_ReleaseTLibAttr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ SYS_WIN64 ; 
 scalar_t__ TKIND_DISPATCH ; 

__attribute__((used)) static HRESULT get_iface_info(ITypeInfo **typeinfo, WORD *funcs, WORD *parentfuncs,
        GUID *parentiid)
{
    ITypeInfo *real_typeinfo, *parentinfo;
    TYPEATTR *typeattr;
    ITypeLib *typelib;
    TLIBATTR *libattr;
    TYPEKIND typekind;
    HREFTYPE reftype;
    SYSKIND syskind;
    HRESULT hr;

    /* Dual interfaces report their size to be sizeof(IDispatchVtbl) and their
     * implemented type to be IDispatch. We need to retrieve the underlying
     * interface to get that information. */
    hr = ITypeInfo_GetTypeAttr(*typeinfo, &typeattr);
    if (FAILED(hr))
        return hr;
    typekind = typeattr->typekind;
    ITypeInfo_ReleaseTypeAttr(*typeinfo, typeattr);
    if (typekind == TKIND_DISPATCH)
    {
        hr = ITypeInfo_GetRefTypeOfImplType(*typeinfo, -1, &reftype);
        if (FAILED(hr))
            return hr;

        hr = ITypeInfo_GetRefTypeInfo(*typeinfo, reftype, &real_typeinfo);
        if (FAILED(hr))
            return hr;

        ITypeInfo_Release(*typeinfo);
        *typeinfo = real_typeinfo;
    }

    hr = ITypeInfo_GetContainingTypeLib(*typeinfo, &typelib, NULL);
    if (FAILED(hr))
        return hr;

    hr = ITypeLib_GetLibAttr(typelib, &libattr);
    if (FAILED(hr))
    {
        ITypeLib_Release(typelib);
        return hr;
    }
    syskind = libattr->syskind;
    ITypeLib_ReleaseTLibAttr(typelib, libattr);
    ITypeLib_Release(typelib);

    hr = ITypeInfo_GetTypeAttr(*typeinfo, &typeattr);
    if (FAILED(hr))
        return hr;
    *funcs = typeattr->cFuncs;
    *parentfuncs = typeattr->cbSizeVft / (syskind == SYS_WIN64 ? 8 : 4) - *funcs;
    ITypeInfo_ReleaseTypeAttr(*typeinfo, typeattr);

    hr = ITypeInfo_GetRefTypeOfImplType(*typeinfo, 0, &reftype);
    if (FAILED(hr))
        return hr;
    hr = ITypeInfo_GetRefTypeInfo(*typeinfo, reftype, &parentinfo);
    if (FAILED(hr))
        return hr;
    hr = ITypeInfo_GetTypeAttr(parentinfo, &typeattr);
    if (FAILED(hr))
        return hr;
    *parentiid = typeattr->guid;
    ITypeInfo_ReleaseTypeAttr(parentinfo, typeattr);
    ITypeInfo_Release(parentinfo);

    return hr;
}