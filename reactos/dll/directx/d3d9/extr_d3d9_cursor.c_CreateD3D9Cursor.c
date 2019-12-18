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
struct _Direct3DSwapChain9_INT {int dwWidth; int dwHeight; } ;
struct _Direct3DDevice9_INT {int dummy; } ;
struct TYPE_3__ {int dwWidth; int dwHeight; struct _Direct3DSwapChain9_INT* pSwapChain; struct _Direct3DDevice9_INT* pBaseDevice; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_1__ D3D9Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  AlignedAlloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 

D3D9Cursor* CreateD3D9Cursor(struct _Direct3DDevice9_INT* pBaseDevice, struct _Direct3DSwapChain9_INT* pSwapChain)
{
    D3D9Cursor* pCursor;
    
    if (FAILED(AlignedAlloc((LPVOID*)&pCursor, sizeof(D3D9Cursor))))
    {
        DPRINT1("Failed to allocate D3D9Cursor");
        return NULL;
    }

    pCursor->pBaseDevice = pBaseDevice;
    pCursor->pSwapChain = pSwapChain;
    pCursor->dwWidth = pSwapChain->dwWidth / 2;
    pCursor->dwHeight = pSwapChain->dwHeight / 2;

    return pCursor;
}