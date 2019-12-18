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
typedef  size_t UINT ;
struct TYPE_11__ {size_t number_of_cp; TYPE_1__* mime_cp_info; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int ref; int total; TYPE_2__ IEnumCodePage_iface; int /*<<< orphan*/ * cpinfo; scalar_t__ pos; } ;
struct TYPE_8__ {int flags; } ;
typedef  int /*<<< orphan*/  MLang_impl ;
typedef  int /*<<< orphan*/  MIMECPINFO ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  TYPE_2__ IEnumCodePage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ EnumCodePage_impl ;
typedef  int DWORD ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEnumCodePage_vtbl ; 
 int MIMECONTF_MIME_LATEST ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int,int,...) ; 
 int /*<<< orphan*/  fill_cp_info (TYPE_4__*,size_t,int /*<<< orphan*/ ) ; 
 TYPE_4__* mlang_data ; 

__attribute__((used)) static HRESULT EnumCodePage_create( MLang_impl* mlang, DWORD grfFlags,
                     LANGID LangId, IEnumCodePage** ppEnumCodePage )
{
    EnumCodePage_impl *ecp;
    MIMECPINFO *cpinfo;
    UINT i, n;

    TRACE("%p, %08x, %04x, %p\n", mlang, grfFlags, LangId, ppEnumCodePage);

    if (!grfFlags) /* enumerate internal data base of encodings */
        grfFlags = MIMECONTF_MIME_LATEST;

    ecp = HeapAlloc( GetProcessHeap(), 0, sizeof (EnumCodePage_impl) );
    ecp->IEnumCodePage_iface.lpVtbl = &IEnumCodePage_vtbl;
    ecp->ref = 1;
    ecp->pos = 0;
    ecp->total = 0;
    for (i = 0; i < ARRAY_SIZE(mlang_data); i++)
    {
        for (n = 0; n < mlang_data[i].number_of_cp; n++)
        {
            if (mlang_data[i].mime_cp_info[n].flags & grfFlags)
                ecp->total++;
        }
    }

    ecp->cpinfo = HeapAlloc(GetProcessHeap(), 0,
                            sizeof(MIMECPINFO) * ecp->total);
    cpinfo = ecp->cpinfo;

    for (i = 0; i < ARRAY_SIZE(mlang_data); i++)
    {
        for (n = 0; n < mlang_data[i].number_of_cp; n++)
        {
            if (mlang_data[i].mime_cp_info[n].flags & grfFlags)
                fill_cp_info(&mlang_data[i], n, cpinfo++);
        }
    }

    TRACE("enumerated %d codepages with flags %08x\n", ecp->total, grfFlags);

    *ppEnumCodePage = &ecp->IEnumCodePage_iface;

    return S_OK;
}