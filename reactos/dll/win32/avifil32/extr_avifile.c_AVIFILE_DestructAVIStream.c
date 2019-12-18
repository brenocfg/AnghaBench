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
struct TYPE_4__ {scalar_t__ cb; int /*<<< orphan*/ * lp; } ;
struct TYPE_5__ {int lLastFrame; scalar_t__ cbFormat; int /*<<< orphan*/ * lpFormat; TYPE_1__ extra; scalar_t__ cbHandlerData; int /*<<< orphan*/ * lpHandlerData; scalar_t__ cbBuffer; int /*<<< orphan*/ * lpBuffer; int /*<<< orphan*/ * idxFmtChanges; scalar_t__ nIdxFrames; int /*<<< orphan*/ * idxFrames; int /*<<< orphan*/ * paf; scalar_t__ dwCurrentFrame; } ;
typedef  TYPE_2__ IAVIStreamImpl ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void    AVIFILE_DestructAVIStream(IAVIStreamImpl *This)
{
  /* pre-conditions */
  assert(This != NULL);

  This->dwCurrentFrame = (DWORD)-1;
  This->lLastFrame    = -1;
  This->paf = NULL;
  if (This->idxFrames != NULL) {
    HeapFree(GetProcessHeap(), 0, This->idxFrames);
    This->idxFrames  = NULL;
    This->nIdxFrames = 0;
  }
  HeapFree(GetProcessHeap(), 0, This->idxFmtChanges);
  This->idxFmtChanges = NULL;
  if (This->lpBuffer != NULL) {
    HeapFree(GetProcessHeap(), 0, This->lpBuffer);
    This->lpBuffer = NULL;
    This->cbBuffer = 0;
  }
  if (This->lpHandlerData != NULL) {
    HeapFree(GetProcessHeap(), 0, This->lpHandlerData);
    This->lpHandlerData = NULL;
    This->cbHandlerData = 0;
  }
  if (This->extra.lp != NULL) {
    HeapFree(GetProcessHeap(), 0, This->extra.lp);
    This->extra.lp = NULL;
    This->extra.cb = 0;
  }
  if (This->lpFormat != NULL) {
    HeapFree(GetProcessHeap(), 0, This->lpFormat);
    This->lpFormat = NULL;
    This->cbFormat = 0;
  }
}