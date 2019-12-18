#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int ref; TYPE_4__ IUnknown_inner; TYPE_4__* outer_unk; TYPE_3__ IAVIStream_iface; TYPE_2__ IPersistFile_iface; TYPE_1__ IAVIFile_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_4__ IUnknown ;
typedef  TYPE_5__ IAVIFileImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_MEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_5__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (TYPE_4__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  iwavft ; 
 int /*<<< orphan*/  iwavpft ; 
 int /*<<< orphan*/  iwavst ; 
 int /*<<< orphan*/  unk_vtbl ; 

HRESULT AVIFILE_CreateWAVFile(IUnknown *outer_unk, REFIID riid, void **ret_iface)
{
    IAVIFileImpl *pfile;
    HRESULT hr;

    *ret_iface = NULL;

    pfile = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*pfile));
    if (!pfile)
        return AVIERR_MEMORY;

    pfile->IUnknown_inner.lpVtbl = &unk_vtbl;
    pfile->IAVIFile_iface.lpVtbl = &iwavft;
    pfile->IPersistFile_iface.lpVtbl = &iwavpft;
    pfile->IAVIStream_iface.lpVtbl = &iwavst;
    pfile->ref = 1;
    if (outer_unk)
        pfile->outer_unk = outer_unk;
    else
        pfile->outer_unk = &pfile->IUnknown_inner;

    hr = IUnknown_QueryInterface(&pfile->IUnknown_inner, riid, ret_iface);
    IUnknown_Release(&pfile->IUnknown_inner);

    return hr;
}