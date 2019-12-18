#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_16__ {TYPE_1__* lpVtbl; } ;
struct TYPE_15__ {int /*<<< orphan*/  szLinkName; int /*<<< orphan*/  szWorkingDirectory; int /*<<< orphan*/  szDescription; scalar_t__ szTarget; } ;
struct TYPE_14__ {scalar_t__ (* Load ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* Save ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetWorkingDirectory ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetDescription ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetPath ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__* PCREATE_LINK_CONTEXT ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCOLESTR ;
typedef  TYPE_3__ IShellLinkW ;
typedef  TYPE_3__ IPersistFile ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_ShellLink ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  IID_IPersistFile ; 
 int /*<<< orphan*/  IID_IShellLinkW ; 
 scalar_t__ IShellLinkW_GetPath (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IUnknown_QueryInterface (TYPE_3__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_3__*) ; 
 scalar_t__ IsExtensionAShortcut (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathFindExtensionW (scalar_t__) ; 
 int /*<<< orphan*/  STGM_READ ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  StringCchCopyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
CreateShortcut(PCREATE_LINK_CONTEXT pContext)
{
    IShellLinkW *pShellLink, *pSourceShellLink;
    IPersistFile *pPersistFile;
    HRESULT hr;
    WCHAR Path[MAX_PATH];
    LPWSTR lpExtension;

    /* get the extension */
    lpExtension = PathFindExtensionW(pContext->szTarget);

    if (IsExtensionAShortcut(lpExtension))
    {
        hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_ALL, &IID_IShellLinkW, (void**)&pSourceShellLink);

        if (FAILED(hr))
            return FALSE;

        hr = IUnknown_QueryInterface(pSourceShellLink, &IID_IPersistFile, (void**)&pPersistFile);
        if (FAILED(hr))
        {
            IUnknown_Release(pSourceShellLink);
            return FALSE;
        }

        hr = pPersistFile->lpVtbl->Load(pPersistFile, (LPCOLESTR)pContext->szTarget, STGM_READ);
        IUnknown_Release(pPersistFile);

        if (FAILED(hr))
        {
            IUnknown_Release(pSourceShellLink);
            return FALSE;
        }

        hr = IShellLinkW_GetPath(pSourceShellLink, Path, _countof(Path), NULL, 0);
        IUnknown_Release(pSourceShellLink);

        if (FAILED(hr))
        {
            return FALSE;
        }
    }
    else
    {
        StringCchCopyW(Path, _countof(Path), pContext->szTarget);
    }

    hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_ALL,
                          &IID_IShellLinkW, (void**)&pShellLink);

    if (hr != S_OK)
        return FALSE;

    pShellLink->lpVtbl->SetPath(pShellLink, Path);
    pShellLink->lpVtbl->SetDescription(pShellLink, pContext->szDescription);
    pShellLink->lpVtbl->SetWorkingDirectory(pShellLink, pContext->szWorkingDirectory);

    hr = IUnknown_QueryInterface(pShellLink, &IID_IPersistFile, (void**)&pPersistFile);
    if (hr != S_OK)
    {
        IUnknown_Release(pShellLink);
        return FALSE;
    }

    hr = pPersistFile->lpVtbl->Save(pPersistFile, pContext->szLinkName, TRUE);
    IUnknown_Release(pPersistFile);
    IUnknown_Release(pShellLink);
    return (hr == S_OK);
}