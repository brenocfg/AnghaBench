#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* lpadesc; TYPE_3__* lptdesc; } ;
struct TYPE_7__ {int vt; TYPE_2__ u; } ;
struct TYPE_5__ {size_t cDims; TYPE_3__ tdescElem; } ;
typedef  TYPE_3__ TYPEDESC ;
typedef  int SIZE_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYDESC ; 
 scalar_t__ FALSE ; 
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
#define  VT_CARRAY 130 
#define  VT_PTR 129 
#define  VT_SAFEARRAY 128 
 int /*<<< orphan*/ * rgbounds ; 

__attribute__((used)) static SIZE_T TLB_SizeTypeDesc( const TYPEDESC *tdesc, BOOL alloc_initial_space )
{
    SIZE_T size = 0;

    if (alloc_initial_space)
        size += sizeof(TYPEDESC);

    switch (tdesc->vt)
    {
    case VT_PTR:
    case VT_SAFEARRAY:
        size += TLB_SizeTypeDesc(tdesc->u.lptdesc, TRUE);
        break;
    case VT_CARRAY:
        size += FIELD_OFFSET(ARRAYDESC, rgbounds[tdesc->u.lpadesc->cDims]);
        size += TLB_SizeTypeDesc(&tdesc->u.lpadesc->tdescElem, FALSE);
        break;
    }
    return size;
}