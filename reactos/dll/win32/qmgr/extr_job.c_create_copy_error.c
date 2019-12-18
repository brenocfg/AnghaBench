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
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct copy_error {int refs; TYPE_1__ IBackgroundCopyError_iface; int /*<<< orphan*/ * file; int /*<<< orphan*/  code; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  IBackgroundCopyFile2 ;
typedef  TYPE_1__ IBackgroundCopyError ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BG_ERROR_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct copy_error* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IBackgroundCopyFile2_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  copy_error_vtbl ; 

__attribute__((used)) static HRESULT create_copy_error(
    BG_ERROR_CONTEXT context,
    HRESULT code,
    IBackgroundCopyFile2 *file,
    IBackgroundCopyError **obj)
{
    struct copy_error *error;

    TRACE("context %u code %08x file %p\n", context, code, file);

    if (!(error = HeapAlloc(GetProcessHeap(), 0, sizeof(*error) ))) return E_OUTOFMEMORY;
    error->IBackgroundCopyError_iface.lpVtbl = &copy_error_vtbl;
    error->refs    = 1;
    error->context = context;
    error->code    = code;
    error->file    = file;
    if (error->file) IBackgroundCopyFile2_AddRef(error->file);

    *obj = &error->IBackgroundCopyError_iface;
    TRACE("returning iface %p\n", *obj);
    return S_OK;
}