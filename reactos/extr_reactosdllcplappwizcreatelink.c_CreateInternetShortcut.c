#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {TYPE_1__* lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/  szTarget; int /*<<< orphan*/  szLinkName; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* Save ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetURL ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* PCREATE_LINK_CONTEXT ;
typedef  TYPE_3__ IUniformResourceLocatorW ;
typedef  TYPE_3__ IPersistFile ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_InternetShortcut ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetFullPathNameW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IPersistFile ; 
 int /*<<< orphan*/  IID_IUniformResourceLocatorW ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (TYPE_3__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_3__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL
CreateInternetShortcut(PCREATE_LINK_CONTEXT pContext)
{
    IUniformResourceLocatorW *pURL = NULL;
    IPersistFile *pPersistFile = NULL;
    HRESULT hr;
    WCHAR szPath[MAX_PATH];
    GetFullPathNameW(pContext->szLinkName, _countof(szPath), szPath, NULL);

    hr = CoCreateInstance(&CLSID_InternetShortcut, NULL, CLSCTX_ALL,
                          &IID_IUniformResourceLocatorW, (void **)&pURL);
    if (FAILED(hr))
        return FALSE;

    hr = IUnknown_QueryInterface(pURL, &IID_IPersistFile, (void **)&pPersistFile);
    if (FAILED(hr))
    {
        IUnknown_Release(pURL);
        return FALSE;
    }

    pURL->lpVtbl->SetURL(pURL, pContext->szTarget, 0);

    hr = pPersistFile->lpVtbl->Save(pPersistFile, szPath, TRUE);

    IUnknown_Release(pPersistFile);
    IUnknown_Release(pURL);

    return SUCCEEDED(hr);
}