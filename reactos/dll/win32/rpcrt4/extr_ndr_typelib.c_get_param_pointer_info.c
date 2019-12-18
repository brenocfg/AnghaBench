#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int vt; int /*<<< orphan*/  hreftype; TYPE_1__* lptdesc; } ;
struct TYPE_11__ {unsigned short cbSizeInstance; int /*<<< orphan*/  typekind; TYPE_2__ tdescAlias; } ;
struct TYPE_9__ {int vt; int /*<<< orphan*/  hreftype; } ;
typedef  TYPE_2__ TYPEDESC ;
typedef  TYPE_3__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 unsigned char FC_ENUM32 ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 unsigned short IsBasetype ; 
 unsigned short IsSimpleRef ; 
 unsigned short MustFree ; 
 int /*<<< orphan*/  S_OK ; 
#define  TKIND_ALIAS 138 
#define  TKIND_COCLASS 137 
#define  TKIND_DISPATCH 136 
#define  TKIND_ENUM 135 
#define  TKIND_INTERFACE 134 
#define  TKIND_RECORD 133 
#define  VT_CARRAY 132 
#define  VT_DISPATCH 131 
#define  VT_PTR 130 
#define  VT_UNKNOWN 129 
#define  VT_USERDEFINED 128 
 unsigned char get_base_type (int) ; 
 unsigned short type_memsize (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static HRESULT get_param_pointer_info(ITypeInfo *typeinfo, TYPEDESC *tdesc, int is_in,
        int is_out, unsigned short *server_size, unsigned short *flags,
        unsigned char *basetype, TYPEDESC **tfs_tdesc)
{
    ITypeInfo *refinfo;
    HRESULT hr = S_OK;
    TYPEATTR *attr;

    switch (tdesc->vt)
    {
    case VT_UNKNOWN:
    case VT_DISPATCH:
        *flags |= MustFree;
        if (is_in && is_out)
            *server_size = sizeof(void *);
        break;
    case VT_PTR:
        *flags |= MustFree;

        if (tdesc->lptdesc->vt == VT_USERDEFINED)
        {
            ITypeInfo_GetRefTypeInfo(typeinfo, tdesc->lptdesc->hreftype, &refinfo);
            ITypeInfo_GetTypeAttr(refinfo, &attr);

            switch (attr->typekind)
            {
            case TKIND_INTERFACE:
            case TKIND_DISPATCH:
            case TKIND_COCLASS:
                if (is_in && is_out)
                    *server_size = sizeof(void *);
                break;
            default:
                *server_size = sizeof(void *);
            }

            ITypeInfo_ReleaseTypeAttr(refinfo, attr);
            ITypeInfo_Release(refinfo);
        }
        else
            *server_size = sizeof(void *);
        break;
    case VT_CARRAY:
        *flags |= IsSimpleRef | MustFree;
        *server_size = type_memsize(typeinfo, tdesc);
        *tfs_tdesc = tdesc;
        break;
    case VT_USERDEFINED:
        ITypeInfo_GetRefTypeInfo(typeinfo, tdesc->hreftype, &refinfo);
        ITypeInfo_GetTypeAttr(refinfo, &attr);

        switch (attr->typekind)
        {
        case TKIND_ENUM:
            *flags |= IsSimpleRef | IsBasetype;
            if (!is_in && is_out)
                *server_size = sizeof(void *);
            *basetype = FC_ENUM32;
            break;
        case TKIND_RECORD:
            *flags |= IsSimpleRef | MustFree;
            if (!is_in && is_out)
                *server_size = attr->cbSizeInstance;
            *tfs_tdesc = tdesc;
            break;
        case TKIND_INTERFACE:
        case TKIND_DISPATCH:
        case TKIND_COCLASS:
            *flags |= MustFree;
            break;
        case TKIND_ALIAS:
            hr = get_param_pointer_info(refinfo, &attr->tdescAlias, is_in,
                    is_out, server_size, flags, basetype, tfs_tdesc);
            break;
        default:
            FIXME("unhandled kind %#x\n", attr->typekind);
            hr = E_NOTIMPL;
            break;
        }

        ITypeInfo_ReleaseTypeAttr(refinfo, attr);
        ITypeInfo_Release(refinfo);
        break;
    default:
        *flags |= IsSimpleRef;
        *tfs_tdesc = tdesc;
        if (!is_in && is_out)
            *server_size = type_memsize(typeinfo, tdesc);
        if ((*basetype = get_base_type(tdesc->vt)))
            *flags |= IsBasetype;
        break;
    }

    return hr;
}