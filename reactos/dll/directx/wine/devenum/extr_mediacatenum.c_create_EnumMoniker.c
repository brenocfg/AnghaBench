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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_1__ IEnumMoniker_iface; int /*<<< orphan*/  dmo_enum; int /*<<< orphan*/ * cm_key; int /*<<< orphan*/ * sw_key; int /*<<< orphan*/  class; scalar_t__ cm_index; scalar_t__ sw_index; } ;
typedef  int /*<<< orphan*/ * REFCLSID ;
typedef  TYPE_1__ IEnumMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ EnumMonikerImpl ;

/* Variables and functions */
 int /*<<< orphan*/  CHARS_IN_GUID ; 
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  DEVENUM_LockModule () ; 
 int /*<<< orphan*/  DMOEnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IEnumMoniker_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  IEnumMoniker_Vtbl ; 
 int /*<<< orphan*/  KEY_ENUMERATE_SUB_KEYS ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backslashW ; 
 int /*<<< orphan*/  clsidW ; 
 int /*<<< orphan*/  instanceW ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wszActiveMovieKey ; 

HRESULT create_EnumMoniker(REFCLSID class, IEnumMoniker **ppEnumMoniker)
{
    EnumMonikerImpl * pEnumMoniker = CoTaskMemAlloc(sizeof(EnumMonikerImpl));
    WCHAR buffer[78];
    HRESULT hr;

    if (!pEnumMoniker)
        return E_OUTOFMEMORY;

    pEnumMoniker->IEnumMoniker_iface.lpVtbl = &IEnumMoniker_Vtbl;
    pEnumMoniker->ref = 1;
    pEnumMoniker->sw_index = 0;
    pEnumMoniker->cm_index = 0;
    pEnumMoniker->class = *class;

    lstrcpyW(buffer, clsidW);
    lstrcatW(buffer, backslashW);
    StringFromGUID2(class, buffer + lstrlenW(buffer), CHARS_IN_GUID);
    lstrcatW(buffer, instanceW);
    if (RegOpenKeyExW(HKEY_CLASSES_ROOT, buffer, 0, KEY_ENUMERATE_SUB_KEYS, &pEnumMoniker->sw_key))
        pEnumMoniker->sw_key = NULL;

    lstrcpyW(buffer, wszActiveMovieKey);
    StringFromGUID2(class, buffer + lstrlenW(buffer), CHARS_IN_GUID);
    if (RegOpenKeyExW(HKEY_CURRENT_USER, buffer, 0, KEY_ENUMERATE_SUB_KEYS, &pEnumMoniker->cm_key))
        pEnumMoniker->cm_key = NULL;

    hr = DMOEnum(class, 0, 0, NULL, 0, NULL, &pEnumMoniker->dmo_enum);
    if (FAILED(hr))
    {
        IEnumMoniker_Release(&pEnumMoniker->IEnumMoniker_iface);
        return hr;
    }

    *ppEnumMoniker = &pEnumMoniker->IEnumMoniker_iface;

    DEVENUM_LockModule();

    return S_OK;
}