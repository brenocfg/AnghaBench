#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IWshShortcut_iface; int /*<<< orphan*/  classinfo; int /*<<< orphan*/  link; int /*<<< orphan*/  path_link; } ;
typedef  TYPE_2__ WshShortcut ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ShellLink ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IShellLinkW ; 
 int /*<<< orphan*/  IID_IWshShortcut ; 
 int /*<<< orphan*/  IShellLinkW_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WshShortcutVtbl ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  init_classinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT WshShortcut_Create(const WCHAR *path, IDispatch **shortcut)
{
    WshShortcut *This;
    HRESULT hr;

    *shortcut = NULL;

    This = heap_alloc(sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IWshShortcut_iface.lpVtbl = &WshShortcutVtbl;
    This->ref = 1;

    hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
            &IID_IShellLinkW, (void**)&This->link);
    if (FAILED(hr))
    {
        heap_free(This);
        return hr;
    }

    This->path_link = SysAllocString(path);
    if (!This->path_link)
    {
        IShellLinkW_Release(This->link);
        heap_free(This);
        return E_OUTOFMEMORY;
    }

    init_classinfo(&IID_IWshShortcut, (IUnknown *)&This->IWshShortcut_iface, &This->classinfo);
    *shortcut = (IDispatch*)&This->IWshShortcut_iface;

    return S_OK;
}