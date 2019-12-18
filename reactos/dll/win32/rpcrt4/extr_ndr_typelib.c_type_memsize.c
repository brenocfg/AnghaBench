#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_11__ {unsigned int cbSizeInstance; } ;
struct TYPE_10__ {int vt; int /*<<< orphan*/  hreftype; TYPE_2__* lpadesc; } ;
struct TYPE_9__ {unsigned int cDims; TYPE_1__* rgbounds; TYPE_3__ tdescElem; } ;
struct TYPE_8__ {unsigned int cElements; } ;
typedef  TYPE_3__ TYPEDESC ;
typedef  TYPE_4__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_4__*) ; 
#define  VT_BOOL 151 
#define  VT_BSTR 150 
#define  VT_CARRAY 149 
#define  VT_DATE 148 
#define  VT_DISPATCH 147 
#define  VT_ERROR 146 
#define  VT_HRESULT 145 
#define  VT_I1 144 
#define  VT_I2 143 
#define  VT_I4 142 
#define  VT_I8 141 
#define  VT_INT 140 
#define  VT_PTR 139 
#define  VT_R4 138 
#define  VT_R8 137 
#define  VT_SAFEARRAY 136 
#define  VT_UI1 135 
#define  VT_UI2 134 
#define  VT_UI4 133 
#define  VT_UI8 132 
#define  VT_UINT 131 
#define  VT_UNKNOWN 130 
#define  VT_USERDEFINED 129 
#define  VT_VARIANT 128 

__attribute__((used)) static unsigned int type_memsize(ITypeInfo *typeinfo, TYPEDESC *desc)
{
    switch (desc->vt)
    {
    case VT_I1:
    case VT_UI1:
        return 1;
    case VT_I2:
    case VT_UI2:
    case VT_BOOL:
        return 2;
    case VT_I4:
    case VT_UI4:
    case VT_R4:
    case VT_INT:
    case VT_UINT:
    case VT_ERROR:
    case VT_HRESULT:
        return 4;
    case VT_I8:
    case VT_UI8:
    case VT_R8:
    case VT_DATE:
        return 8;
    case VT_BSTR:
    case VT_SAFEARRAY:
    case VT_PTR:
    case VT_UNKNOWN:
    case VT_DISPATCH:
        return sizeof(void *);
    case VT_VARIANT:
        return sizeof(VARIANT);
    case VT_CARRAY:
    {
        unsigned int size = type_memsize(typeinfo, &desc->lpadesc->tdescElem);
        unsigned int i;
        for (i = 0; i < desc->lpadesc->cDims; i++)
            size *= desc->lpadesc->rgbounds[i].cElements;
        return size;
    }
    case VT_USERDEFINED:
    {
        unsigned int size = 0;
        ITypeInfo *refinfo;
        TYPEATTR *attr;

        ITypeInfo_GetRefTypeInfo(typeinfo, desc->hreftype, &refinfo);
        ITypeInfo_GetTypeAttr(refinfo, &attr);
        size = attr->cbSizeInstance;
        ITypeInfo_ReleaseTypeAttr(refinfo, attr);
        ITypeInfo_Release(refinfo);
        return size;
    }
    default:
        FIXME("unhandled type %u\n", desc->vt);
        return 0;
    }
}