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
struct TYPE_3__ {int /*<<< orphan*/ * pdsfd; scalar_t__ ref; int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/ * LPUNKNOWN ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDFULLDUPLEX ;
typedef  TYPE_1__ IDirectSoundFullDuplex_IUnknown ;
typedef  int /*<<< orphan*/  IDirectSoundFullDuplexImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_INVALIDPARAM ; 
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  DirectSoundFullDuplex_Unknown_Vtbl ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static HRESULT IDirectSoundFullDuplex_IUnknown_Create(
    LPDIRECTSOUNDFULLDUPLEX pdsfd,
    LPUNKNOWN * ppunk)
{
    IDirectSoundFullDuplex_IUnknown * pdsfdunk;
    TRACE("(%p,%p)\n",pdsfd,ppunk);

    if (pdsfd == NULL) {
        ERR("invalid parameter: pdsfd == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (ppunk == NULL) {
        ERR("invalid parameter: ppunk == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    pdsfdunk = HeapAlloc(GetProcessHeap(),0,sizeof(*pdsfdunk));
    if (pdsfdunk == NULL) {
        WARN("out of memory\n");
        *ppunk = NULL;
        return DSERR_OUTOFMEMORY;
    }

    pdsfdunk->lpVtbl = &DirectSoundFullDuplex_Unknown_Vtbl;
    pdsfdunk->ref = 0;
    pdsfdunk->pdsfd = (IDirectSoundFullDuplexImpl *)pdsfd;

    *ppunk = (LPUNKNOWN)pdsfdunk;

    return DS_OK;
}