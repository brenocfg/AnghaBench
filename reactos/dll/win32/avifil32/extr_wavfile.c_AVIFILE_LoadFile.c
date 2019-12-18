#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int nBlockAlign; int /*<<< orphan*/  nAvgBytesPerSec; } ;
struct TYPE_15__ {int dwLength; int dwSampleSize; int dwScale; int dwSuggestedBufferSize; int /*<<< orphan*/  dwRate; int /*<<< orphan*/  fccType; } ;
struct TYPE_13__ {scalar_t__ fccType; scalar_t__ cksize; int dwDataOffset; int /*<<< orphan*/  ckid; } ;
struct TYPE_12__ {int dwStreams; } ;
struct TYPE_14__ {scalar_t__ cbFormat; int /*<<< orphan*/  hmmio; int /*<<< orphan*/  extra; TYPE_2__ ckData; TYPE_6__ sInfo; TYPE_7__* lpFormat; TYPE_1__ fInfo; int /*<<< orphan*/  fDirty; } ;
typedef  TYPE_2__ MMCKINFO ;
typedef  TYPE_3__ IAVIFileImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_BADFORMAT ; 
 int /*<<< orphan*/  AVIERR_FILEREAD ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int /*<<< orphan*/  AVIFILE_LoadSunFile (TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FindChunkAndKeepExtras (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_7__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MMIO_FINDCHUNK ; 
 int /*<<< orphan*/  MMIO_FINDRIFF ; 
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  ckidWAVEDATA ; 
 int /*<<< orphan*/  ckidWAVEFORMAT ; 
 scalar_t__ formtypeWAVE ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmioAscend (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioDescend (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int mmioSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streamtypeAUDIO ; 

__attribute__((used)) static HRESULT AVIFILE_LoadFile(IAVIFileImpl *This)
{
  MMCKINFO ckRIFF;
  MMCKINFO ck;

  This->sInfo.dwLength = 0; /* just to be sure */
  This->fDirty = FALSE;

  /* search for RIFF chunk */
  ckRIFF.fccType = 0; /* find any */
  if (mmioDescend(This->hmmio, &ckRIFF, NULL, MMIO_FINDRIFF) != S_OK) {
    return AVIFILE_LoadSunFile(This);
  }

  if (ckRIFF.fccType != formtypeWAVE)
    return AVIERR_BADFORMAT;

  /* search WAVE format chunk */
  ck.ckid = ckidWAVEFORMAT;
  if (FindChunkAndKeepExtras(&This->extra, This->hmmio, &ck,
			     &ckRIFF, MMIO_FINDCHUNK) != S_OK)
    return AVIERR_FILEREAD;

  /* get memory for format and read it */
  This->lpFormat = HeapAlloc(GetProcessHeap(), 0, ck.cksize);
  if (This->lpFormat == NULL)
    return AVIERR_FILEREAD;
  This->cbFormat = ck.cksize;

  if (mmioRead(This->hmmio, (HPSTR)This->lpFormat, ck.cksize) != ck.cksize)
    return AVIERR_FILEREAD;
  if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEREAD;

  /* Non-pcm formats have a fact chunk.
   * We don't need it, so simply add it to the extra chunks.
   */

  /* find the big data chunk */
  This->ckData.ckid = ckidWAVEDATA;
  if (FindChunkAndKeepExtras(&This->extra, This->hmmio, &This->ckData,
			     &ckRIFF, MMIO_FINDCHUNK) != S_OK)
    return AVIERR_FILEREAD;

  memset(&This->sInfo, 0, sizeof(This->sInfo));
  This->sInfo.fccType      = streamtypeAUDIO;
  This->sInfo.dwRate       = This->lpFormat->nAvgBytesPerSec;
  This->sInfo.dwSampleSize =
    This->sInfo.dwScale    = This->lpFormat->nBlockAlign;
  This->sInfo.dwLength     = This->ckData.cksize / This->lpFormat->nBlockAlign;
  This->sInfo.dwSuggestedBufferSize = This->ckData.cksize;

  This->fInfo.dwStreams = 1;

  if (mmioAscend(This->hmmio, &This->ckData, 0) != S_OK) {
    /* seems to be truncated */
    WARN(": file seems to be truncated!\n");
    This->ckData.cksize  = mmioSeek(This->hmmio, 0, SEEK_END) -
      This->ckData.dwDataOffset;
    This->sInfo.dwLength = This->ckData.cksize / This->lpFormat->nBlockAlign;
    This->sInfo.dwSuggestedBufferSize = This->ckData.cksize;
  }

  /* ignore errors */
  FindChunkAndKeepExtras(&This->extra, This->hmmio, &ck, &ckRIFF, 0);

  return AVIERR_OK;
}