#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  hreftype; TYPE_2__* lpadesc; } ;
struct TYPE_9__ {int vt; TYPE_3__ u; } ;
struct TYPE_7__ {int cDims; TYPE_4__ tdescElem; TYPE_1__* rgbounds; } ;
struct TYPE_6__ {int cElements; } ;
typedef  TYPE_4__ TYPEDESC ;
typedef  int /*<<< orphan*/  SYSKIND ;
typedef  int /*<<< orphan*/  ITypeInfoImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DECIMAL ;
typedef  int /*<<< orphan*/  DATE ;
typedef  int /*<<< orphan*/  CY ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  SYS_WIN32 ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TLB_get_size_from_hreftype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
#define  VT_BOOL 156 
#define  VT_BSTR 155 
#define  VT_CARRAY 154 
#define  VT_CY 153 
#define  VT_DATE 152 
#define  VT_DECIMAL 151 
#define  VT_DISPATCH 150 
#define  VT_ERROR 149 
#define  VT_HRESULT 148 
#define  VT_I1 147 
#define  VT_I2 146 
#define  VT_I4 145 
#define  VT_I8 144 
#define  VT_INT 143 
#define  VT_LPSTR 142 
#define  VT_LPWSTR 141 
#define  VT_PTR 140 
#define  VT_R4 139 
#define  VT_R8 138 
#define  VT_SAFEARRAY 137 
#define  VT_UI1 136 
#define  VT_UI2 135 
#define  VT_UI4 134 
#define  VT_UI8 133 
#define  VT_UINT 132 
#define  VT_UNKNOWN 131 
#define  VT_USERDEFINED 130 
#define  VT_VARIANT 129 
#define  VT_VOID 128 
 int get_ptr_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT TLB_size_instance(ITypeInfoImpl *info, SYSKIND sys,
        TYPEDESC *tdesc, ULONG *size, WORD *align)
{
    ULONG i, sub, ptr_size;
    HRESULT hr;

    ptr_size = get_ptr_size(sys);

    switch(tdesc->vt){
    case VT_VOID:
        *size = 0;
        break;
    case VT_I1:
    case VT_UI1:
        *size = 1;
        break;
    case VT_I2:
    case VT_BOOL:
    case VT_UI2:
        *size = 2;
        break;
    case VT_I4:
    case VT_R4:
    case VT_ERROR:
    case VT_UI4:
    case VT_INT:
    case VT_UINT:
    case VT_HRESULT:
        *size = 4;
        break;
    case VT_R8:
    case VT_I8:
    case VT_UI8:
        *size = 8;
        break;
    case VT_BSTR:
    case VT_DISPATCH:
    case VT_UNKNOWN:
    case VT_PTR:
    case VT_SAFEARRAY:
    case VT_LPSTR:
    case VT_LPWSTR:
        *size = ptr_size;
        break;
    case VT_DATE:
        *size = sizeof(DATE);
        break;
    case VT_VARIANT:
        *size = sizeof(VARIANT);
#ifdef _WIN64
        if(sys == SYS_WIN32)
            *size -= 8; /* 32-bit VARIANT is 8 bytes smaller than 64-bit VARIANT */
#endif
        break;
    case VT_DECIMAL:
        *size = sizeof(DECIMAL);
        break;
    case VT_CY:
        *size = sizeof(CY);
        break;
    case VT_CARRAY:
        *size = 0;
        for(i = 0; i < tdesc->u.lpadesc->cDims; ++i)
            *size += tdesc->u.lpadesc->rgbounds[i].cElements;
        hr = TLB_size_instance(info, sys, &tdesc->u.lpadesc->tdescElem, &sub, align);
        if(FAILED(hr))
            return hr;
        *size *= sub;
        return S_OK;
    case VT_USERDEFINED:
        return TLB_get_size_from_hreftype(info, tdesc->u.hreftype, size, align);
    default:
        FIXME("Unsized VT: 0x%x\n", tdesc->vt);
        return E_FAIL;
    }

    if(align){
        if(*size < 4)
            *align = *size;
        else
            *align = 4;
    }

    return S_OK;
}