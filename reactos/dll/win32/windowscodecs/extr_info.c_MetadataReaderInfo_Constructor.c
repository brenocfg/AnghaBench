#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  const* lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_6__ IWICComponentInfo_iface; int /*<<< orphan*/  clsid; } ;
struct TYPE_7__ {TYPE_2__ base; int /*<<< orphan*/  classkey; } ;
typedef  int /*<<< orphan*/ * REFCLSID ;
typedef  TYPE_1__ MetadataReaderInfo ;
typedef  int /*<<< orphan*/  IWICComponentInfoVtbl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  TYPE_2__ ComponentInfo ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IWICComponentInfo_Release (TYPE_6__*) ; 
 int /*<<< orphan*/  MetadataReaderInfo_Vtbl ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WINCODEC_ERR_COMPONENTNOTFOUND ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  read_metadata_info (TYPE_1__*) ; 

__attribute__((used)) static HRESULT MetadataReaderInfo_Constructor(HKEY classkey, REFCLSID clsid, ComponentInfo **info)
{
    MetadataReaderInfo *This;

    This = heap_alloc_zero(sizeof(*This));
    if (!This)
    {
        RegCloseKey(classkey);
        return E_OUTOFMEMORY;
    }

    This->base.IWICComponentInfo_iface.lpVtbl = (const IWICComponentInfoVtbl*)&MetadataReaderInfo_Vtbl;
    This->base.ref = 1;
    This->classkey = classkey;
    This->base.clsid = *clsid;

    if (!read_metadata_info(This))
    {
        IWICComponentInfo_Release(&This->base.IWICComponentInfo_iface);
        return WINCODEC_ERR_COMPONENTNOTFOUND;
    }

    *info = &This->base;
    return S_OK;
}