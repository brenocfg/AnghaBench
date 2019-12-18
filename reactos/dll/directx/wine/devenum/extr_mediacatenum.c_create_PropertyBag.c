#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  class; scalar_t__ has_class; int /*<<< orphan*/  clsid; } ;
struct TYPE_7__ {int ref; scalar_t__ type; TYPE_3__ IPropertyBag_iface; scalar_t__ path; int /*<<< orphan*/  clsid; } ;
typedef  TYPE_1__ RegPropBagImpl ;
typedef  TYPE_2__ MediaCatMoniker ;
typedef  TYPE_3__ IPropertyBag ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHARS_IN_GUID ; 
 TYPE_1__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  DEVENUM_LockModule () ; 
 scalar_t__ DEVICE_CODEC ; 
 scalar_t__ DEVICE_DMO ; 
 scalar_t__ DEVICE_FILTER ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IPropertyBag_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backslashW ; 
 int /*<<< orphan*/  clsidW ; 
 int /*<<< orphan*/  instanceW ; 
 int /*<<< orphan*/  lstrcatW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lstrlenW (scalar_t__) ; 
 int /*<<< orphan*/  wszActiveMovieKey ; 

__attribute__((used)) static HRESULT create_PropertyBag(MediaCatMoniker *mon, IPropertyBag **ppBag)
{
    RegPropBagImpl * rpb = CoTaskMemAlloc(sizeof(RegPropBagImpl));
    if (!rpb)
        return E_OUTOFMEMORY;
    rpb->IPropertyBag_iface.lpVtbl = &IPropertyBag_Vtbl;
    rpb->ref = 1;
    rpb->type = mon->type;

    if (rpb->type == DEVICE_DMO)
        rpb->clsid = mon->clsid;
    else if (rpb->type == DEVICE_FILTER)
    {
        lstrcpyW(rpb->path, clsidW);
        lstrcatW(rpb->path, backslashW);
        if (mon->has_class)
        {
            StringFromGUID2(&mon->class, rpb->path + lstrlenW(rpb->path), CHARS_IN_GUID);
            lstrcatW(rpb->path, instanceW);
            lstrcatW(rpb->path, backslashW);
        }
        lstrcatW(rpb->path, mon->name);
    }
    else if (rpb->type == DEVICE_CODEC)
    {
        lstrcpyW(rpb->path, wszActiveMovieKey);
        if (mon->has_class)
        {
            StringFromGUID2(&mon->class, rpb->path + lstrlenW(rpb->path), CHARS_IN_GUID);
            lstrcatW(rpb->path, backslashW);
        }
        lstrcatW(rpb->path, mon->name);
    }

    *ppBag = &rpb->IPropertyBag_iface;
    DEVENUM_LockModule();
    return S_OK;
}