#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct folder {int ref; TYPE_1__ IFolder_iface; int /*<<< orphan*/  classinfo; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IFolder ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_Folder ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  foldervtbl ; 
 struct folder* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (struct folder*) ; 
 int /*<<< orphan*/  init_classinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT create_folder(const WCHAR *path, IFolder **folder)
{
    struct folder *This;

    *folder = NULL;

    TRACE("%s\n", debugstr_w(path));

    This = heap_alloc(sizeof(struct folder));
    if (!This) return E_OUTOFMEMORY;

    This->IFolder_iface.lpVtbl = &foldervtbl;
    This->ref = 1;
    This->path = SysAllocString(path);
    if (!This->path)
    {
        heap_free(This);
        return E_OUTOFMEMORY;
    }

    init_classinfo(&CLSID_Folder, (IUnknown *)&This->IFolder_iface, &This->classinfo);
    *folder = &This->IFolder_iface;

    return S_OK;
}