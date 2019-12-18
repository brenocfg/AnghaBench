#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dwSuggestedBufferSize; } ;
struct TYPE_11__ {TYPE_2__* lpFrame; TYPE_1__ sInfo; int /*<<< orphan*/ * pg; int /*<<< orphan*/ * pCurStream; } ;
struct TYPE_10__ {int /*<<< orphan*/  biSizeImage; } ;
typedef  int /*<<< orphan*/ * PGETFRAME ;
typedef  int /*<<< orphan*/ * PAVISTREAM ;
typedef  TYPE_2__* LPVOID ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_3__ IAVIEditStreamImpl ;

/* Variables and functions */
 TYPE_2__* AVIStreamGetFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIStreamGetFrameClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * AVIStreamGetFrameOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ IGetFrame_SetFormat (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPVOID AVIFILE_ReadFrame(IAVIEditStreamImpl* const This,
                                PAVISTREAM pstream, LONG pos)
{
  PGETFRAME pg;

  TRACE("(%p,%p,%d)\n",This,pstream,pos);

  if (pstream == NULL)
    return NULL;

  /* if stream changes make sure that only palette changes */
  if (This->pCurStream != pstream) {
    pg = AVIStreamGetFrameOpen(pstream, NULL);
    if (pg == NULL)
      return NULL;
    if (This->pg != NULL) {
      if (IGetFrame_SetFormat(pg, This->lpFrame, NULL, 0, 0, -1, -1) != S_OK) {
        AVIStreamGetFrameClose(pg);
        ERR(": IGetFrame_SetFormat failed\n");
        return NULL;
      }
      AVIStreamGetFrameClose(This->pg);
    }
    This->pg         = pg;
    This->pCurStream = pstream;
  }

  /* now get the decompressed frame */
  This->lpFrame = AVIStreamGetFrame(This->pg, pos);
  if (This->lpFrame != NULL)
    This->sInfo.dwSuggestedBufferSize = This->lpFrame->biSizeImage;

  return This->lpFrame;
}