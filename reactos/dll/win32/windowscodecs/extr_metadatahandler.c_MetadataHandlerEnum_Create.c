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
struct TYPE_8__ {int /*<<< orphan*/  IWICMetadataWriter_iface; } ;
struct TYPE_7__ {int ref; TYPE_3__ IWICEnumMetadataItem_iface; int /*<<< orphan*/  index; TYPE_2__* parent; } ;
typedef  TYPE_1__ MetadataHandlerEnum ;
typedef  TYPE_2__ MetadataHandler ;
typedef  TYPE_3__ IWICEnumMetadataItem ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWICMetadataWriter_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MetadataHandlerEnum_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT MetadataHandlerEnum_Create(MetadataHandler *parent, DWORD index,
    IWICEnumMetadataItem **ppIEnumMetadataItem)
{
    MetadataHandlerEnum *This;

    if (!ppIEnumMetadataItem) return E_INVALIDARG;

    *ppIEnumMetadataItem = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(MetadataHandlerEnum));
    if (!This) return E_OUTOFMEMORY;

    IWICMetadataWriter_AddRef(&parent->IWICMetadataWriter_iface);

    This->IWICEnumMetadataItem_iface.lpVtbl = &MetadataHandlerEnum_Vtbl;
    This->ref = 1;
    This->parent = parent;
    This->index = index;

    *ppIEnumMetadataItem = &This->IWICEnumMetadataItem_iface;

    return S_OK;
}