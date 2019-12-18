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
typedef  int WORD ;
struct TYPE_4__ {int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HREFTYPE ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int IMPLTYPEFLAG_FDEFAULT ; 
 int /*<<< orphan*/  ITypeInfo_GetImplTypeFlags (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeOfImplType (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void get_default_iface(ITypeInfo *typeinfo, WORD count, GUID *iid)
{
    ITypeInfo *refinfo;
    HREFTYPE reftype;
    TYPEATTR *attr;
    int flags, i;

    for (i = 0; i < count; ++i)
    {
        ITypeInfo_GetImplTypeFlags(typeinfo, i, &flags);
        if (flags & IMPLTYPEFLAG_FDEFAULT)
            break;
    }

    /* If no interface was explicitly marked default, choose the first one. */
    if (i == count)
        i = 0;

    ITypeInfo_GetRefTypeOfImplType(typeinfo, i, &reftype);
    ITypeInfo_GetRefTypeInfo(typeinfo, reftype, &refinfo);
    ITypeInfo_GetTypeAttr(refinfo, &attr);
    *iid = attr->guid;
    ITypeInfo_ReleaseTypeAttr(refinfo, attr);
    ITypeInfo_Release(refinfo);
}