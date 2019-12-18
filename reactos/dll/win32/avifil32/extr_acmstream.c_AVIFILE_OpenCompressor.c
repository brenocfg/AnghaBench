#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nAvgBytesPerSec; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_6__ {int /*<<< orphan*/  dwSuggestedBufferSize; int /*<<< orphan*/  dwLength; int /*<<< orphan*/  dwStart; int /*<<< orphan*/  rcFrame; scalar_t__ dwQuality; int /*<<< orphan*/  dwRate; int /*<<< orphan*/  dwScale; int /*<<< orphan*/  dwSampleSize; } ;
struct TYPE_7__ {int cbInFormat; int cbOutFormat; TYPE_1__ sInfo; TYPE_3__* lpOutFormat; int /*<<< orphan*/ * lpInFormat; int /*<<< orphan*/ * has; int /*<<< orphan*/ * pStream; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_2__ IAVIStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_FORMATSUGGESTF_WFORMATTAG ; 
 int /*<<< orphan*/  ACM_STREAMOPENF_NONREALTIME ; 
 int /*<<< orphan*/  AVIERR_ERROR ; 
 int /*<<< orphan*/  AVIERR_MEMORY ; 
 int /*<<< orphan*/  AVIERR_NOCOMPRESSOR ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int /*<<< orphan*/  AVIStreamFormatSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CONVERT_STREAM_to_THIS (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IAVIStream_ReadFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ ICQUALITY_DEFAULT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetRectEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 scalar_t__ acmFormatSuggest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ acmStreamOpen (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT AVIFILE_OpenCompressor(IAVIStreamImpl *This)
{
  HRESULT hr;

  /* pre-conditions */
  assert(This != NULL);
  assert(This->pStream != NULL);

  if (This->has != NULL)
    return AVIERR_OK;

  if (This->lpInFormat == NULL) {
    /* decode or encode the data from pStream */
    hr = AVIStreamFormatSize(This->pStream, This->sInfo.dwStart, &This->cbInFormat);
    if (FAILED(hr))
      return hr;
    This->lpInFormat = HeapAlloc(GetProcessHeap(), 0, This->cbInFormat);
    if (This->lpInFormat == NULL)
      return AVIERR_MEMORY;

    hr = IAVIStream_ReadFormat(This->pStream, This->sInfo.dwStart,
                               This->lpInFormat, &This->cbInFormat);
    if (FAILED(hr))
      return hr;

    if (This->lpOutFormat == NULL) {
      /* we must decode to default format */
      This->cbOutFormat = sizeof(PCMWAVEFORMAT);
      This->lpOutFormat = HeapAlloc(GetProcessHeap(), 0, This->cbOutFormat);
      if (This->lpOutFormat == NULL)
        return AVIERR_MEMORY;

      This->lpOutFormat->wFormatTag = WAVE_FORMAT_PCM;
      if (acmFormatSuggest(NULL, This->lpInFormat, This->lpOutFormat,
                           This->cbOutFormat, ACM_FORMATSUGGESTF_WFORMATTAG) != S_OK)
        return AVIERR_NOCOMPRESSOR;
    }
  } else if (This->lpOutFormat == NULL)
    return AVIERR_ERROR; /* To what should I encode? */

  if (acmStreamOpen(&This->has, NULL, This->lpInFormat, This->lpOutFormat,
                    NULL, 0, 0, ACM_STREAMOPENF_NONREALTIME) != S_OK)
    return AVIERR_NOCOMPRESSOR;

  /* update AVISTREAMINFO structure */
  This->sInfo.dwSampleSize = This->lpOutFormat->nBlockAlign;
  This->sInfo.dwScale      = This->lpOutFormat->nBlockAlign;
  This->sInfo.dwRate       = This->lpOutFormat->nAvgBytesPerSec;
  This->sInfo.dwQuality    = (DWORD)ICQUALITY_DEFAULT;
  SetRectEmpty(&This->sInfo.rcFrame);

  /* convert positions and sizes to output format */
  CONVERT_STREAM_to_THIS(&This->sInfo.dwStart);
  CONVERT_STREAM_to_THIS(&This->sInfo.dwLength);
  CONVERT_STREAM_to_THIS(&This->sInfo.dwSuggestedBufferSize);

  return AVIERR_OK;
}