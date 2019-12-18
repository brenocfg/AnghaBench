#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list {int dummy; } ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  entry; int /*<<< orphan*/ * guid; } ;
typedef  int /*<<< orphan*/  TLBGuid ;
typedef  TYPE_1__ TLBCustData ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_BADVARTYPE ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 TYPE_1__* TLB_get_custdata_by_guid (struct list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLB_get_guid_null (int /*<<< orphan*/ *) ; 
#define  VT_BSTR 134 
#define  VT_HRESULT 133 
#define  VT_I4 132 
#define  VT_INT 131 
#define  VT_R4 130 
#define  VT_UI4 129 
#define  VT_UINT 128 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  list_add_tail (struct list*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT TLB_set_custdata(struct list *custdata_list, TLBGuid *tlbguid, VARIANT *var)
{
    TLBCustData *cust_data;

    switch(V_VT(var)){
    case VT_I4:
    case VT_R4:
    case VT_UI4:
    case VT_INT:
    case VT_UINT:
    case VT_HRESULT:
    case VT_BSTR:
        break;
    default:
        return DISP_E_BADVARTYPE;
    }

    cust_data = TLB_get_custdata_by_guid(custdata_list, TLB_get_guid_null(tlbguid));

    if (!cust_data) {
        cust_data = heap_alloc(sizeof(TLBCustData));
        if (!cust_data)
            return E_OUTOFMEMORY;

        cust_data->guid = tlbguid;
        VariantInit(&cust_data->data);

        list_add_tail(custdata_list, &cust_data->entry);
    }else
        VariantClear(&cust_data->data);

    return VariantCopy(&cust_data->data, var);
}