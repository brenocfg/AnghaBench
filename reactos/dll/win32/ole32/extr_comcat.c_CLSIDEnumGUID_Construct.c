#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct class_categories {int dummy; } ;
typedef  char WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IEnumGUID_iface; int /*<<< orphan*/  key; struct class_categories* categories; } ;
typedef  TYPE_1__ IEnumCLSID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ CLSID_IEnumGUIDImpl ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDEnumGUIDVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  open_classes_key (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT CLSIDEnumGUID_Construct(struct class_categories *categories, IEnumCLSID **ret)
{
    static const WCHAR keyname[] = {'C','L','S','I','D',0};
    CLSID_IEnumGUIDImpl *This;

    *ret = NULL;

    This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CLSID_IEnumGUIDImpl));
    if (!This) return E_OUTOFMEMORY;

    This->IEnumGUID_iface.lpVtbl = &CLSIDEnumGUIDVtbl;
    This->ref = 1;
    This->categories = categories;
    open_classes_key(HKEY_CLASSES_ROOT, keyname, KEY_READ, &This->key);

    *ret = &This->IEnumGUID_iface;

    return S_OK;
}