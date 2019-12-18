#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ dwMoviChunkPos; int dwNextFramePos; int /*<<< orphan*/  hmmio; int /*<<< orphan*/  fDirty; } ;
struct TYPE_9__ {TYPE_6__* paf; } ;
struct TYPE_8__ {scalar_t__ dwDataOffset; scalar_t__ fccType; scalar_t__ cksize; int /*<<< orphan*/  ckid; } ;
typedef  TYPE_1__ MMCKINFO ;
typedef  int /*<<< orphan*/ * LPCVOID ;
typedef  scalar_t__ LONG ;
typedef  TYPE_2__ IAVIStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FOURCC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_FILEWRITE ; 
 int /*<<< orphan*/  AVIFILE_AddFrame (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIFILE_ComputeMoviStart (TYPE_6__*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ mmioAscend (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioCreateChunk (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mmioSeek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static HRESULT AVIFILE_WriteBlock(IAVIStreamImpl *This, DWORD block,
				  FOURCC ckid, DWORD flags, LPCVOID buffer,
				  LONG size)
{
  MMCKINFO ck;

  ck.ckid    = ckid;
  ck.cksize  = size;
  ck.fccType = 0;

  /* if no frame/block is already written, we must compute start of movi chunk */
  if (This->paf->dwMoviChunkPos == 0)
    AVIFILE_ComputeMoviStart(This->paf);

  if (mmioSeek(This->paf->hmmio, This->paf->dwNextFramePos, SEEK_SET) == -1)
    return AVIERR_FILEWRITE;

  if (mmioCreateChunk(This->paf->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;
  if (buffer != NULL && size > 0) {
    if (mmioWrite(This->paf->hmmio, buffer, size) != size)
      return AVIERR_FILEWRITE;
  }
  if (mmioAscend(This->paf->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;

  This->paf->fDirty         = TRUE;
  This->paf->dwNextFramePos = mmioSeek(This->paf->hmmio, 0, SEEK_CUR);

  return AVIFILE_AddFrame(This, ckid, size,
			  ck.dwDataOffset - 2 * sizeof(DWORD), flags);
}