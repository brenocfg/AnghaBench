#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  clsid; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pITfThreadMgrEx; int /*<<< orphan*/ * pITfTextInputProcessor; int /*<<< orphan*/  tid; TYPE_1__ LanguageProfile; } ;
typedef  int /*<<< orphan*/  ITfThreadMgrEx ;
typedef  int /*<<< orphan*/  ITfThreadMgr ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ ActivatedTextService ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_ITfTextInputProcessor ; 
 int /*<<< orphan*/  ITfTextInputProcessor_Activate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITfTextInputProcessor_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfThreadMgrEx_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT activate_given_ts(ActivatedTextService *actsvr, ITfThreadMgrEx *tm)
{
    HRESULT hr;

    /* Already Active? */
    if (actsvr->pITfTextInputProcessor)
        return S_OK;

    hr = CoCreateInstance (&actsvr->LanguageProfile.clsid, NULL, CLSCTX_INPROC_SERVER,
        &IID_ITfTextInputProcessor, (void**)&actsvr->pITfTextInputProcessor);
    if (FAILED(hr)) return hr;

    hr = ITfTextInputProcessor_Activate(actsvr->pITfTextInputProcessor, (ITfThreadMgr *)tm, actsvr->tid);
    if (FAILED(hr))
    {
        ITfTextInputProcessor_Release(actsvr->pITfTextInputProcessor);
        actsvr->pITfTextInputProcessor = NULL;
        return hr;
    }

    actsvr->pITfThreadMgrEx = tm;
    ITfThreadMgrEx_AddRef(tm);
    return hr;
}