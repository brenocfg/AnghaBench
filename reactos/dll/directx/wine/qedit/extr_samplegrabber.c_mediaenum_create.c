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
struct TYPE_9__ {int cbFormat; int /*<<< orphan*/  majortype; int /*<<< orphan*/ * pbFormat; int /*<<< orphan*/ * pUnk; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int refCount; TYPE_2__ IEnumMediaTypes_iface; TYPE_3__ mtype; int /*<<< orphan*/  past; } ;
typedef  TYPE_1__ ME_Impl ;
typedef  TYPE_2__ IEnumMediaTypes ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_3__ AM_MEDIA_TYPE ;

/* Variables and functions */
 void* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  IEnumMediaTypes_VTable ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static IEnumMediaTypes *mediaenum_create(const AM_MEDIA_TYPE *mtype, BOOL past)
{
    ME_Impl *obj = CoTaskMemAlloc(sizeof(ME_Impl));

    if (!obj)
        return NULL;
    ZeroMemory(obj, sizeof(*obj));
    obj->IEnumMediaTypes_iface.lpVtbl = &IEnumMediaTypes_VTable;
    obj->refCount = 1;
    obj->past = past;
    if (mtype) {
        obj->mtype = *mtype;
        obj->mtype.pUnk = NULL;
        if (mtype->cbFormat) {
            obj->mtype.pbFormat = CoTaskMemAlloc(mtype->cbFormat);
            CopyMemory(obj->mtype.pbFormat, mtype->pbFormat, mtype->cbFormat);
        }
        else
            obj->mtype.pbFormat = NULL;
    }
    else
        obj->mtype.majortype = GUID_NULL;

    return &obj->IEnumMediaTypes_iface;
}